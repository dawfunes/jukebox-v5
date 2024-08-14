/**
 * @file fsm_jukebox.c
 * @brief Jukebox FSM main file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 22/04/2024
 */

/* Includes ------------------------------------------------------------------*/
// Standard C includes
#include <stdlib.h>
#include <string.h> // strcmp
#include <stdio.h>  // sprintf

// Other includes
#include <fsm.h>
#include "fsm_jukebox.h"
#include "fsm_button.h"
#include "fsm_usart.h"
#include "fsm_buzzer.h"
#include "port_system.h"
#include "port_usart.h"

// v5
#include "fsm_keypad.h"
#include "port_keypad.h"

/* Defines ------------------------------------------------------------------*/
#define MAX(a, b) ((a) > (b) ? (a) : (b)) /*!< Macro to get the maximum of two values. */

/* Private functions */
/**
 * @brief Parse the message received by the USART.
 * 
 * Given data received by the USART, this function parses the message and extracts the command and the parameter (if available).
 * 
 * > 1. Split the message by space using function `strtok()` \n
 * > 2. If there's a token (command), copy it to the `p_command` variable. Otherwise, return `false` \n
 * > 3. Extract the parameter (if available). To do so, get the next token using function `strtok()`. If there's a token, copy it to the `p_param` variable. Otherwise, copy an empty string to the `p_param` variable \n
 * > 4. Return `true` indicating that the message has been parsed correctly \n
 * 
 * @param p_message Pointer to the message received by the USART.
 * @param p_command Pointer to store the command extracted from the message. 
 * @param p_param Pointer to store the parameter extracted from the message. 
 * @return true if the message has been parsed correctly 
 * @return false if the message has not been parsed correctly 
 */
bool _parse_message(char *p_message, char *p_command, char *p_param)
{
    char *p_token = strtok(p_message, " "); // Split the message by space

    // If there's a token (command), copy it to the command variable
    if (p_token != NULL)
    {
        strcpy(p_command, p_token);
    }
    else
    {
        // No command found, you might return an error or handle it as needed
        // The USART driver of the computer sends an empty at initialization, so we will ignore it
        return false;
    }

    // Extract the parameter (if available)
    p_token = strtok(NULL, " "); // Get the next token

    if (p_token != NULL)
    {
        strcpy(p_param, p_token);
    }
    else
    {
        strcpy(p_param, " "); // NO param found
    }
    return true;
}

/**
 * @brief sets the song to the next one in the jukebox and plays it.
 * 
 * @param p_fsm_jukebox pointer to a FSM with a FSM jukebox in it.
 */
void _set_next_song(fsm_jukebox_t * p_fsm_jukebox)
{
    // 1.
    fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, STOP);

    // 2.
    p_fsm_jukebox->melody_idx++;
    if(p_fsm_jukebox->melody_idx >= MELODIES_MEMORY_SIZE){
        p_fsm_jukebox->melody_idx=0;
    }

    // 3.
    if(p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx].melody_length <= 0){
        p_fsm_jukebox->melody_idx=0;
    }
    p_fsm_jukebox->p_melody=p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx].p_name;

    // 4.
    printf("Playing: %s\n", p_fsm_jukebox->p_melody);

    // 5.
    fsm_buzzer_set_melody(p_fsm_jukebox->p_fsm_buzzer, p_fsm_jukebox->melodies+p_fsm_jukebox->melody_idx);
    
    // 6.
    fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);
}

/**
 * @brief Executes the command.
 * 
 * @param p_fsm_jukebox pointer to a FSM with a FSM jukebox in it.
 * @param p_command Pointer that contains the command extracted from the message.
 * @param p_param Pointer that contains the parameter extracted from the message.
 */
void _execute_command(fsm_jukebox_t * p_fsm_jukebox, char * p_command, char * p_param)
{
    // https://sdg2dieupm.github.io/jukebox/fsm_jukebox_execute_command.png
    if (!strcmp(p_command, "play"))
    {
        fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);
        printf("Playing: %s\n", p_fsm_jukebox->p_melody);
    }
    else if (!strcmp(p_command, "stop"))
    {
        fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, STOP);
        printf("Stopped\n");
    }
    else if (!strcmp(p_command, "pause"))
    {
        fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PAUSE);
        printf("Paused\n");
    }
    else if (!strcmp(p_command, "speed"))
    {
        double param = atof(p_param);
        double speed = MAX(param, 0.1);
        fsm_buzzer_set_speed(p_fsm_jukebox->p_fsm_buzzer, speed);
    }
    else if (!strcmp(p_command, "next"))
    {
        _set_next_song(p_fsm_jukebox);
        printf("Playing: %s\n", p_fsm_jukebox->p_melody);
    }
    else if (!strcmp(p_command, "select"))
    {
        uint32_t melody_selected =atoi(p_param);
        if (p_fsm_jukebox->melodies[melody_selected].melody_length != 0)
        {
            fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, STOP);
            p_fsm_jukebox->melody_idx=melody_selected;
            fsm_buzzer_set_melody(p_fsm_jukebox->p_fsm_buzzer, p_fsm_jukebox->melodies+p_fsm_jukebox->melody_idx);
            p_fsm_jukebox->p_melody=p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx].p_name;
            fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);
            printf("Playing: %s\n", p_fsm_jukebox->p_melody);
        }
        else
        {
            char msg[USART_OUTPUT_BUFFER_LENGTH];
            sprintf(msg, "Error: Melody not found\n");
            fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg);
        }
        
    }
    else if (!strcmp(p_command, "info"))
    {
        char msg[USART_OUTPUT_BUFFER_LENGTH];
        if (p_param[0]!=' ')
        {
            uint32_t melody_selected =atoi(p_param);
            if (p_fsm_jukebox->melodies[melody_selected].melody_length != 0 && melody_selected<MELODIES_MEMORY_SIZE)
            {
                sprintf(msg, "[%ld]: %s\n",melody_selected , p_fsm_jukebox->melodies[melody_selected].p_name);
                printf("[%ld]: %s\n",melody_selected , p_fsm_jukebox->melodies[melody_selected].p_name);
                fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg);
            }
            else
            {
                sprintf(msg, "Error: Melody not found\n");
                printf("Error: Melody not found\n");
                fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg);
            }
        }
        else{
            sprintf(msg, "Playing: %s\n", p_fsm_jukebox->p_melody);
            printf("Playing: %s\n", p_fsm_jukebox->p_melody);
            fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg);
        }
        
    }
    else if(!strcmp(p_command, "list")){
        char msg1[USART_OUTPUT_BUFFER_LENGTH];
        sprintf(msg1, "|");
        for (size_t i = 0; i < MELODIES_MEMORY_SIZE; i++)
        {
            char msg2[USART_OUTPUT_BUFFER_LENGTH];
            sprintf(msg2, " [%d]: %s |",i , p_fsm_jukebox->melodies[i].p_name);
            printf("|%s\n", msg2);
            strcat(msg1,msg2);
        }
        strcat(msg1, "\n");
        fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg1);
    }
    else if(!strcmp(p_command, "help")){
        char msg[USART_OUTPUT_BUFFER_LENGTH];
        
        if (!strcmp(p_param, "1"))
        {
            sprintf(msg, "List of commands: 'play' to play current song | 'stop' to stop current song | 'pause' to pause current song | \n");
            printf("\nList of commands:\n+'play' to play current song.\n+'stop' to stop current song.\n+'pause' to pause current song.\n\n");
        }
        else if (!strcmp(p_param, "2"))
        {
            sprintf(msg, "List of commands: 'speed' to change the player speed | 'next' to play the next song | 'select' to select a specific song | \n");
            printf("List of commands:\n+'speed' to change the player speed.\n+'next' to play the next song.\n+'select' to select a specific song.\n\n");
        }
        else if (!strcmp(p_param, "3"))
        {
            sprintf(msg, "List of commands: 'info' to get information about a song | 'list' to see the list of songs | \n");
            printf("List of commands:\n+'info' to get information about a song.\n+'list' to see the list of songs.\n\n");
        }
        else if (!strcmp(p_param, "play"))
        {
            sprintf(msg, "play command: 'play' to play current song. No parameter needed.\n");
            printf("play command:\n'play' to play current song.\n No parameter needed.\n\n");
        }
        else if (!strcmp(p_param, "stop"))
        {
            sprintf(msg, "stop command: 'stop' to stop current song. After being stopped, it can't be resumed with play, it will just restart. No parameter needed.\n");
            printf("stop command:\n'stop' to stop current song. After being stopped, it can't be resumed with play, it will just restart.\n No parameter needed.\n\n");
        }
        else if (!strcmp(p_param, "pause"))
        {
            sprintf(msg, "pause command: 'pause' to pause current song. After being paused, it can be resumed with play. No parameter needed.\n");
            printf("pause command:\n'pause' to pause current song. After being paused, it can be resumed with play.\nNo parameter needed.\n\n");
        }
        else if (!strcmp(p_param, "speed"))
        {
            sprintf(msg, "speed command: 'speed' to change the speed of the current player (0.1 is the minimum). The parameter is a double that we will set the player speed to.\n");
            printf("speed command:\n'speed' to change the speed of the current player (0.1 is the minimum).\nThe parameter is a double that we will set the player speed to.\n\n");
        }
        else if (!strcmp(p_param, "next"))
        {
            sprintf(msg, "next command: 'next' to play the next song. No parameter needed.\n");
            printf("next command:\n'next' to play the next song.\nNo parameter needed.\n\n");
        }
        else if (!strcmp(p_param, "info"))
        {
            sprintf(msg, "info command: 'info' to get information about either the current song or other. The parameter is the id(an integer) of the song we want the info of. If there's no parameter, it gives info of the current song.\n");
            printf("info command:\n'info' to get information about either the current song or other.\nThe parameter is the id(an integer) of the song we want the info of. If there's no parameter, it gives info of the current song.\n\n");
        }
        else if (!strcmp(p_param, "list"))
        {
            sprintf(msg, "list command: 'list' to get a list of all songs and their ids. No parameter needed.\n");
            printf("list command:\n'list' to get a list of all songs and their ids.\nNo parameter needed.\n\n");
        }
        else if (p_param[0]=='s')
        {
            sprintf(msg, "select command: 'select' to change the current song. The parameter is an integer that we will set the song id to.\n");
            printf("select command:\n'select' to change the current song.\nThe parameter is an integer that we will set the song id to.\n\n");
        }
        else
        {
            sprintf(msg, "List of commands: Type 'help _'. Choose a page as the parameter. Pages go 1-3. For more specific help with a certain command, type 'help command', for example, 'help play' if you want help with the play command.\n");
            printf("\nList of commands:\nType 'help _'. Choose a page as the parameter. Pages go 1-3.\nFor more specific help with a certain command, type 'help command', for example, 'help play' if you want help with the play command.\n\n");
        }
        fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg);
    }
    /*else if (!strcmp(p_command, "reverse")){
        uint32_t melody_selected =atoi(p_param);
        if (p_fsm_jukebox->melodies[melody_selected].melody_length != 0)
        {
            fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, STOP);
            p_fsm_jukebox->melody_idx=melody_selected;
            fsm_buzzer_set_reverse_melody(p_fsm_jukebox->p_fsm_buzzer, p_fsm_jukebox->melodies+p_fsm_jukebox->melody_idx);
            p_fsm_jukebox->p_melody=p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx].p_name;
            fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);
        }
        else
        {
            char msg[USART_OUTPUT_BUFFER_LENGTH];
            sprintf(msg, "Error: Melody not found\n");
            fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg);
        }
    }*/
    else
    {
        // Set USART out data "Error: Command not found\n"
        char msg[USART_OUTPUT_BUFFER_LENGTH];
        sprintf(msg, "Error: Command not found\n");
        fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg);
    }
    return;
}


/* State machine input or transition functions */

/**
 * @brief Checks if the button has been pressed for long enough to turn on the jukebox.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 * @return true The button has been pressed long enough to turn it on.
 * @return false The button has not been pressed long enough to turn it on.
 */
static bool check_on(fsm_t * p_this)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    uint32_t duration = fsm_button_get_duration(p_fsm->p_fsm_button);

    // 2.
    return ((duration > 0 && duration > p_fsm->on_off_press_time_ms)/* || ans*/);
}

/**
 * @brief Checks if the button has been pressed for long enough to turn off the jukebox.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 * @return true The button has been pressed long enough to turn it off.
 * @return false The button has not been pressed long enough to turn it off.
 */
static bool check_off(fsm_t * p_this)
{
    // 1.
    return check_on(p_this);
}

/**
 * @brief Checks if the melody is done playing.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 * @return true The current status of the buzzer is STOP, so it is done playing.
 * @return false The current status of the buzzer is not STOP, so it is not done playing.
 */
static bool check_melody_finished(fsm_t * p_this)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    return (fsm_buzzer_get_action(p_fsm->p_fsm_buzzer)==STOP);
}

/**
 * @brief Checks if a command has been received through the USART.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 * @return true A command has been received through the USART.
 * @return false No command has been received.
 */
static bool check_command_received(fsm_t * p_this)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    return fsm_usart_check_data_received(p_fsm->p_fsm_usart);
}

/**
 * @brief Checks if the button has been pressed for long enough to play the next song of the jukebox.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 * @return true The button has been pressed long enough to play the next song.
 * @return false The button has not been pressed long enough to play the next song.
 */
static bool check_next_song_button(fsm_t * p_this)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    uint32_t duration = fsm_button_get_duration(p_fsm->p_fsm_button);

    // 2.
    return (duration > 0 && duration > p_fsm->next_song_press_time_ms && duration < p_fsm->on_off_press_time_ms);
}

/**
 * @brief Checks if there is any kind of activity with the components of the jukebox.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 * @return true There is activity, we can't sleep.
 * @return false There is no activity, we can sleep.
 */
static bool check_activity(fsm_t * p_this)	
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    return (fsm_button_check_activity(p_fsm->p_fsm_button) || fsm_usart_check_activity(p_fsm->p_fsm_usart) || fsm_buzzer_check_activity(p_fsm->p_fsm_buzzer) || /*v5*/ fsm_keypad_check_activity(p_fsm->p_fsm_keypad));
}

/**
 * @brief Checks if there is any kind of activity with the components of the jukebox.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 * @return true There is no activity, we can sleep.
 * @return false There is activity, we can't sleep.
 */
static bool check_no_activity(fsm_t * p_this)
{
    return !check_activity(p_this);
}

/**
 * @brief Version 5 addition. Checks if there has been any keys received from the keypad.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 * @return true A key has been received.
 * @return false No key has been received.
 */
static bool check_key_received(fsm_t * p_this){
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    return fsm_keypad_check_key_received(p_fsm->p_fsm_keypad);
}


/* State machine output or action functions */
/**
 * @brief Turns on the jukebox and sets it up with speed 1, melody 0, enabling the usart rx, and playing the intro scale.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_start_up(fsm_t * p_this)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    fsm_button_reset_duration(p_fsm->p_fsm_button);

    // 2.
    fsm_usart_enable_rx_interrupt(p_fsm->p_fsm_usart);

    // 3.
    printf("Jukebox ON\n");

    // 4.
    fsm_buzzer_set_speed(p_fsm->p_fsm_buzzer, 1.0);

    // 5.
    fsm_buzzer_set_melody(p_fsm->p_fsm_buzzer,p_fsm->melodies);

    // 6.
    fsm_buzzer_set_action(p_fsm->p_fsm_buzzer, PLAY);
}

/**
 * @brief Sets the melody to the first one, the scale.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_start_jukebox(fsm_t * p_this)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    p_fsm->melody_idx=0;

    // 2.
    p_fsm->p_melody = p_fsm->melodies[p_fsm->melody_idx].p_name;
}

/**
 * @brief Turns off the jukebox and plays the outro song.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_stop_jukebox(fsm_t * p_this)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    fsm_button_reset_duration(p_fsm->p_fsm_button);

    // 2.
    fsm_usart_disable_rx_interrupt(p_fsm->p_fsm_usart);
    fsm_usart_disable_tx_interrupt(p_fsm->p_fsm_usart);

    // 3.
    printf("Jukebox OFF\n");

    // 4.
    fsm_buzzer_set_action(p_fsm->p_fsm_buzzer, STOP);

    //v5. Add outro song
    fsm_buzzer_set_melody(p_fsm->p_fsm_buzzer,p_fsm->melodies+MELODIES_MEMORY_SIZE-1);
    fsm_buzzer_set_action(p_fsm->p_fsm_buzzer, PLAY);

}

/**
 * @brief Plays the song after the current one.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_load_next_song(fsm_t * p_this)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    _set_next_song(p_fsm);

    // 2.
    fsm_button_reset_duration(p_fsm->p_fsm_button);
}

/**
 * @brief Reads the command that has been inputted.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_read_command(fsm_t * p_this)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    char p_message[USART_INPUT_BUFFER_LENGTH];
    char p_command[USART_INPUT_BUFFER_LENGTH];
    char p_param[USART_INPUT_BUFFER_LENGTH];

    // 2.
    fsm_usart_get_in_data(p_fsm->p_fsm_usart, p_message);

    // 3.
    _parse_message(p_message,p_command,p_param);

    // 4.
    _execute_command(p_fsm, p_command, p_param);

    // 5.
    fsm_usart_reset_input_data(p_fsm->p_fsm_usart);

    // 6. opcional?¿
    memset(p_message, 0, USART_INPUT_BUFFER_LENGTH); // creo que esta bien?¿
}

/**
 * @brief Sends the jukebox to sleep while being off.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_sleep_off(fsm_t * p_this)
{
    // 1.
    port_system_sleep();
}

/**
 * @brief Sends the jukebox to sleep while waiting for command.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_sleep_wait_command(fsm_t * p_this)
{
    // 1.
    port_system_sleep();
}

/**
 * @brief Sends the jukebox to sleep while being off.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_sleep_while_off(fsm_t * p_this)
{
    // 1.
    port_system_sleep();
}

/**
 * @brief Sends the jukebox to sleep while being on.
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_sleep_while_on(fsm_t * p_this)
{
    // 1.
    port_system_sleep();
}

/**
 * @brief Version 5 addition. Reads the key that has been pressed in the keypad
 * 
 * @param p_this pointer to a FSM with a FSM jukebox in it.
 */
static void do_read_key(fsm_t * p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t *)(p_this);
    char key = fsm_keypad_get_key(p_fsm_jukebox->p_fsm_keypad);
    char *key2=&key;
    uint32_t melody_selected =atoi(key2);
        if (p_fsm_jukebox->melodies[melody_selected].melody_length != 0)
        {
            fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, STOP);
            p_fsm_jukebox->melody_idx=melody_selected;
            fsm_buzzer_set_melody(p_fsm_jukebox->p_fsm_buzzer, p_fsm_jukebox->melodies+p_fsm_jukebox->melody_idx);
            p_fsm_jukebox->p_melody=p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx].p_name;
            fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);
        }
        else
        {
            char msg[USART_OUTPUT_BUFFER_LENGTH];
            sprintf(msg, "Error: Melody not found\n");
            fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg);
        }
}

/* fsm_trans_t */

/**
 * @brief Status transitions of the FSM jukebox.
 * 
 */
static fsm_trans_t fsm_trans_jukebox[] = {
    {OFF, check_no_activity, SLEEP_WHILE_OFF, do_sleep_off},
    {SLEEP_WHILE_OFF, check_no_activity, SLEEP_WHILE_OFF, do_sleep_while_off},
    {SLEEP_WHILE_OFF, check_activity, OFF, NULL},
    {OFF, check_on, START_UP, do_start_up},
    {START_UP, check_melody_finished, WAIT_COMMAND, do_start_jukebox},
    {WAIT_COMMAND, check_next_song_button, WAIT_COMMAND, do_load_next_song},
    {WAIT_COMMAND, check_command_received, WAIT_COMMAND, do_read_command},
    {WAIT_COMMAND, check_key_received,WAIT_COMMAND, do_read_key}, //v5
    {WAIT_COMMAND, check_no_activity, SLEEP_WHILE_ON, do_sleep_wait_command},
    {SLEEP_WHILE_ON, check_no_activity, SLEEP_WHILE_ON, do_sleep_while_on},
    {SLEEP_WHILE_ON, check_activity, WAIT_COMMAND, NULL},
    {WAIT_COMMAND, check_off, OFF, do_stop_jukebox},
    {-1, NULL, -1, NULL}
};

/* Public functions */
fsm_t *fsm_jukebox_new(fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms, /* v5 */fsm_t *p_fsm_keypad)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_jukebox_t));

    fsm_jukebox_init(p_fsm, p_fsm_button, on_off_press_time_ms, p_fsm_usart, p_fsm_buzzer, next_song_press_time_ms, p_fsm_keypad);
    
    return p_fsm;
}

void fsm_jukebox_init(fsm_t *p_this, fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms, /* v5 */ fsm_t *p_fsm_keypad)
{
    fsm_jukebox_t *p_fsm = (fsm_jukebox_t *)(p_this);
    // 1.
    fsm_init(p_this, fsm_trans_jukebox); 

    // 2.
    p_fsm->p_fsm_button = p_fsm_button;
    p_fsm->on_off_press_time_ms = on_off_press_time_ms;
    p_fsm->p_fsm_usart = p_fsm_usart;
    p_fsm->p_fsm_buzzer = p_fsm_buzzer;
    p_fsm->next_song_press_time_ms = next_song_press_time_ms;

    // v5
    p_fsm->p_fsm_keypad = p_fsm_keypad;

    // 3.
    p_fsm->melody_idx = 0;

    // 4.
    memset(p_fsm->melodies,0,sizeof(p_fsm->melodies));

    // 5.
    p_fsm->melodies[0] = scale_melody;
    p_fsm->melodies[1] = tetris_melody;
    p_fsm->melodies[2] = happy_birthday_melody;

    // v.5
    p_fsm->melodies[3] = march_of_the_toreadors;
    p_fsm->melodies[4] = careless_whispers;
    p_fsm->melodies[5] = legend_of_zelda_main;
    p_fsm->melodies[6] = imperial_march;
    p_fsm->melodies[7] = mario_bros_main;
    p_fsm->melodies[8] = pokemon_main;
    p_fsm->melodies[9] = halloween_theme;
    p_fsm->melodies[10] = outro;
}

