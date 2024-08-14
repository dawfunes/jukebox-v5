/**
 * @file fsm_buzzer.c
 * @brief Buzzer melody player FSM main file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz
 * @date 09/04/2024
 */

/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <stdlib.h>

/* Other libraries */
#include "port_buzzer.h"
#include "fsm_buzzer.h"
#include "melodies.h"

/* Private functions */

/**
 * @brief Method to set the frecuency of the PWM and the duration of the note dpending
 * of the player speed.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 * @param freq Frecuency of the note
 * @param duration Duration of the note
 */
static void _start_note(fsm_t * p_this, double 	freq, uint32_t duration){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    double dur=(double)duration/(p_fsm->player_speed);
    port_buzzer_set_note_frequency(p_fsm->buzzer_id, freq);
    port_buzzer_set_note_duration(p_fsm->buzzer_id, dur);
}

/* State machine input or transition functions */
/**
 * @brief Chenk if a song has ended by checking if the note index is greater than the
 * songs lenght.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 * @return true song has ended
 * @return false song hasn't ended
 */
static bool check_end_melody(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return (p_fsm->note_index>=p_fsm->p_melody->melody_length);
//    if(p_fsm->note_index<p_fsm->p_melody->melody_length)
//        return true;
//    else
//        return false;
}

/**
 * @brief Checks if a song has to start if the melody isn't null and user action is play.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 * @return true there is a melody and user action is play
 * @return false there isn't a melody or user action isn't play
 */
static bool check_melody_start(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return (p_fsm->p_melody!=NULL && p_fsm->user_action==PLAY);
//    if(p_fsm->p_melody!=NULL && check_resume(p_this))
//        return true;
//    else
//        return false;
}	

/**
 * @brief Checks if a note has ended by calling the fuction port_buzzer_get_note_timeout
 * and printing the result.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 * @return true note ended
 * @return false noted hasn't end
 */
static bool check_note_end(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return port_buzzer_get_note_timeout(p_fsm->buzzer_id);
}

/**
 * @brief Checks if the user action is pause
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 * @return true user action is Pause
 * @return false user action isn't Pause
 */
static bool check_pause(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return (p_fsm->user_action==PAUSE);
}

/**
 * @brief Checks if the user action is Play and the song hasn't ended.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 * @return true user action is Play and song hasn't ended
 * @return false user action isn't Play or song has ended
 */
static bool check_play_note(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return (p_fsm->user_action==PLAY && !check_end_melody(p_this));
}


/**
 * @brief Checks if the song has to start.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 * @return true has to start
 * @return false doesn't have to start
 */
static bool check_player_start(fsm_t * p_this){
    return check_melody_start(p_this);
}


/**
 * @brief Chekcs if user action is Stop.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 * @return true user action is Stop
 * @return false user action isn't Stop
 */
static bool check_player_stop(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return (p_fsm->user_action==STOP);
}

/**
 * @brief Checks if the user action is Play.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 * @return true user action is Play
 * @return false user action isn't Play
 */
static bool check_resume(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return (p_fsm->user_action==PLAY);
}


/* State machine output or action functions */

/**
 * @brief Stops the song, by calling port_buzzer_stop to stop the PWM and the timer,
 * reset the index of the song by setting the note index to cero and sets user action 
 * to Stop.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 */
static void do_end_melody(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    port_buzzer_stop(p_fsm->buzzer_id);// 1. Call the corresponding function from PORT that stops the PWM and the timer
    p_fsm->note_index=0;    // 2. Reset the index of the melody
    p_fsm->user_action=STOP; //3 Update the action of the player
}

/**
 * @brief Starts a song, first gets the frequency and duration of the first note,
 * then calls the fuction _start_note with this frequency and duration and increments
 * by one note index.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 */
static void do_melody_start(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    double freq = p_fsm->p_melody->p_notes[0];
    uint16_t duration = p_fsm->p_melody->p_durations[0];
    _start_note(p_this, freq, duration);
    p_fsm->note_index++;
}

/**
 * @brief Ends current note by calling port_buzzer_stop to stop the PWM and the timer.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer 
 */
static void do_note_end(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    port_buzzer_stop(p_fsm->buzzer_id);// 1. Call the corresponding function from PORT that stops the PWM and the timer
}

/**
 * @brief Stops current note by calling port_buzzer_stop to stop the PWM and the timer.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 */
static void do_pause(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    port_buzzer_stop(p_fsm->buzzer_id);// 1. Call the corresponding function from PORT that stops the PWM and the timer
}

/**
 * @brief Plays a new note, by geting the frequency and duration of the current
 * note, then calls the fuction _start_note with this frequency and duration 
 * and increments by one note index.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 */
static void do_play_note(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    double freq = p_fsm->p_melody->p_notes[p_fsm->note_index];
    uint16_t duration = p_fsm->p_melody->p_durations[p_fsm->note_index];
    _start_note(p_this, freq, duration);
    p_fsm->note_index++;
}

/**
 * @brief Starts the playser by calling the method do_melody_start.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 */
static void do_player_start(fsm_t * p_this){
    do_melody_start(p_this);
}

/**
 * @brief Stops the player by calling the method port_buzzer_stop
 * and reseting the note index.
 * 
 * @param p_this Pointer to a struct that contins a fsm_buzzer
 */
static void do_player_stop(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    port_buzzer_stop(p_fsm->buzzer_id);// 1. Call the corresponding function from PORT that stops the PWM and the timer
    p_fsm->note_index=0;
}

/* fsm_trans_t */
/**
 * @brief Status transitions of the FSM buzzer.
 * 
 */
static fsm_trans_t fsm_trans_buzzer[] = {
    {WAIT_START, check_player_start, WAIT_NOTE, do_player_start},
    {WAIT_NOTE, check_note_end, PLAY_NOTE, do_note_end},
    {PLAY_NOTE, check_play_note, WAIT_NOTE, do_play_note},
    {PLAY_NOTE, check_player_stop, WAIT_START, do_player_stop},
    {PLAY_NOTE, check_pause, PAUSE_NOTE, do_pause},
    {PLAY_NOTE, check_end_melody, WAIT_MELODY, do_end_melody},
    {PAUSE_NOTE, check_resume, PLAY_NOTE, NULL},
    {WAIT_MELODY, check_melody_start, WAIT_NOTE, do_melody_start},
    {-1, NULL, -1, NULL}
};

/* Public functions */
//fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);


void fsm_buzzer_set_melody(fsm_t * p_this, const melody_t * p_melody){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    p_fsm->p_melody=(melody_t *)p_melody;
}

/*void fsm_buzzer_set_reverse_melody(fsm_t * p_this, const melody_t * p_melody){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    // Creamos nuevo melody_t*
    melody_t *p_reversed_melody = (melody_t *)malloc(sizeof(melody_t));

    p_reversed_melody->p_name = p_melody->p_name;
    p_reversed_melody->melody_length = p_melody->melody_length;

    // Asignar memoria para los arrays invertidos de notas y duraciones
    p_reversed_melody->p_notes = (double *)malloc(p_melody->melody_length * sizeof(int));
    p_reversed_melody->p_durations = (uint16_t *)malloc(p_melody->melody_length * sizeof(int));

    // Invertir los arrays
    for (size_t i = 0; i < p_melody->melody_length; ++i) {
        p_reversed_melody->p_notes[i] = p_melody->p_notes[p_melody->melody_length - 1 - i];
        p_reversed_melody->p_durations[i] = p_melody->p_durations[p_melody->melody_length - 1 - i];
    }

    p_fsm->p_melody = p_reversed_melody;
}*/


void fsm_buzzer_set_speed(fsm_t * p_this, double speed){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    p_fsm->player_speed=speed;
}


void fsm_buzzer_set_action(fsm_t * p_this, uint8_t action){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    p_fsm->user_action=action;
    if (p_fsm->user_action==STOP)
        p_fsm->note_index=0;
}


uint8_t fsm_buzzer_get_action(fsm_t * p_this){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return p_fsm->user_action;
}


fsm_t *fsm_buzzer_new(uint32_t buzzer_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_buzzer_t));
    fsm_buzzer_init(p_fsm, buzzer_id);
    return p_fsm;
}

void fsm_buzzer_init(fsm_t *p_this, uint32_t buzzer_id)
{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    fsm_init(p_this, fsm_trans_buzzer);


    p_fsm->buzzer_id = buzzer_id;
    p_fsm->p_melody = NULL;
    p_fsm->note_index = 0;
    p_fsm->user_action = STOP;
    p_fsm->player_speed = 1.0;
    port_buzzer_init(buzzer_id);
}

bool fsm_buzzer_check_activity(fsm_t * p_this)
{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return (p_fsm->user_action == PLAY);
}