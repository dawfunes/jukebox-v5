/**
 * @file melodies.c
 * @brief Melodies source file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 2024-05-22
 */

/* Includes ------------------------------------------------------------------*/
#include "melodies.h"

/* Melodies ------------------------------------------------------------------*/
// Melody Happy Birthday
#define HAPPY_BIRTHDAY_LENGTH 26 /*!< Happy Birthday melody length */

/**
 * @brief Happy Birthday melody notes.
 *
 * This array contains the frequencies of the notes for the Happy Birthday song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double happy_birthday_notes[HAPPY_BIRTHDAY_LENGTH] = {
    SILENCE, DO4, DO4, RE4, DO4, FA4, MI4, DO4, DO4, RE4, DO4, SOL4, FA4, DO4, DO4, DO5, LA4, FA4, MI4, RE4, LAs4, LAs4, LA4, FA4, SOL4, FA4};

/**
 * @brief Happy Birthday melody durations in miliseconds.
 *
 * This array contains the duration of each note in the Happy Birthday song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t happy_birthday_durations[HAPPY_BIRTHDAY_LENGTH] = {
    100, 300, 100, 400, 400, 400, 800, 300, 100, 400, 400, 400, 800, 300, 100, 400, 400, 400, 400, 400, 300, 100, 400, 400, 400, 800};

/**
 * @brief Happy Birthday melody struct.
 *
 * This struct contains the information of the Happy Birthday melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t happy_birthday_melody = {.p_name = "Happy Birthday",
                                        .p_notes = (double *)happy_birthday_notes,
                                        .p_durations = (uint16_t *)happy_birthday_durations,
                                        .melody_length = HAPPY_BIRTHDAY_LENGTH};

// Tetris melody
#define TETRIS_LENGTH 41 /*!< Tetris melody length */

/**
 * @brief Tetris melody notes.
 *
 * This array contains the frequencies of the notes for the Tetris song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double tetris_notes[TETRIS_LENGTH] = {
    SILENCE, MI5, SI4, DO5, RE5, DO5, SI4, LA4, LA4, DO5, MI5, RE5, DO5, SI4, DO5, RE5, MI5, DO5, LA4,
    LA4, LA4, SI4, DO5, RE5, FA4, LA5, SOL5, FA5, MI5, DO5, MI5, RE5, DO5, SI4, SI4, LA4, RE5,
    MI5, DO5, LA4, LA4};

/** 
 * @brief Tetris melody durations in miliseconds.
 *
 * This array contains the duration of each note in the Tetris song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t tetris_durations[TETRIS_LENGTH] = {
    100, 400, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 600, 200, 400, 400, 400, 400, 200, 200, 200, 200,
    600, 200, 400, 200, 200, 600, 200, 400, 200, 200, 400, 200, 200, 400, 400, 400, 400, 400};

/**
 * @brief Tetris melody struct.
 * 
 * This struct contains the information of the Tetris melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t tetris_melody = {.p_name = "Tetris",
                                .p_notes = (double *)tetris_notes,
                                .p_durations = (uint16_t *)tetris_durations,
                                .melody_length = TETRIS_LENGTH};

// Scale Melody
#define SCALE_MELODY_LENGTH 8   /*!< Scale melody length */

/**
 * @brief Scale melody notes.
 *
 * This array contains the frequencies of the notes for the scale song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double scale_melody_notes[SCALE_MELODY_LENGTH] = {
    DO4, RE4, MI4, FA4, SOL4, LA4, SI4, DO5};

/**
 * @brief Scale melody durations in miliseconds.
 * 
 * This array contains the duration of each note in the scale song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t scale_melody_durations[SCALE_MELODY_LENGTH] = {
    250, 250, 250, 250, 250, 250, 250, 250};

/**
 * @brief Scale melody struct.
 * 
 * This struct contains the information of the scale melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t scale_melody = {.p_name = "Scale",
                               .p_notes = (double *)scale_melody_notes,
                               .p_durations = (uint16_t *)scale_melody_durations,
                               .melody_length = SCALE_MELODY_LENGTH};


////////////////////////// V5 ////////////////////////////////////////////
// Outro song

#define OUTRO_LENGTH 15   /*!< Outro melody length */

/**
 * @brief Outro notes.
 *
 * This array contains the frequencies of the notes for the Outro song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double outro_notes[OUTRO_LENGTH] = {
    SILENCE, SI4, SILENCE, FA5, SILENCE, FA5, FA5, MI5, RE5, DO5, MI4, SOL3, MI4, DO4, SILENCE};

/**
 * @brief Outro durations in miliseconds.
 * 
 * This array contains the duration of each note in the Outro song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t outro_durations[OUTRO_LENGTH] = {
    100, 200, 50, 150, 200, 200, 266, 266, 267, 200, 200, 200, 200, 785, 15};

/**
 * @brief Outro struct.
 * 
 * This struct contains the information of the Outro.
 * It is used to play the melody using the buzzer.
 */
const melody_t outro = {.p_name = "Outro",
                               .p_notes = (double *)outro_notes,
                               .p_durations = (uint16_t *)outro_durations,
                               .melody_length = OUTRO_LENGTH};



// March of the Toreadors 

#define MARCH_OF_THE_TOREADORS_LENGTH 21   /*!< March of the Toreadors melody length */

/**
 * @brief March of the Toreadors notes.
 *
 * This array contains the frequencies of the notes for the March of the Toreadors song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double march_of_the_toreadors_notes[MARCH_OF_THE_TOREADORS_LENGTH] = {
    SILENCE, DO5, RE5, DO5, LA4, SILENCE, LA4, SILENCE,
    LA4, SOL4, LA4, LAs4, LA4, 
    LAs4, SOL4, DO5, LA4,
    FA4, RE4, SOL4, DO4 };

/**
 * @brief March of the toreadors durations in miliseconds.
 * 
 * This array contains the duration of each note in the March of the toreadors song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t march_of_the_toreadors_durations[MARCH_OF_THE_TOREADORS_LENGTH] = {
    100, 400, 300, 100, 150, 100, 150, 100,
    300, 100, 300, 100, 800, 
    400, 300, 100, 800,
    400, 300, 100, 800 };

/**
 * @brief March of the toreadors struct.
 * 
 * This struct contains the information of the March of the toreadors.
 * It is used to play the melody using the buzzer.
 */
const melody_t march_of_the_toreadors = {.p_name = "March of the Toreadors",
                               .p_notes = (double *)march_of_the_toreadors_notes,
                               .p_durations = (uint16_t *)march_of_the_toreadors_durations,
                               .melody_length = MARCH_OF_THE_TOREADORS_LENGTH};



// Careless Whispers

#define CARELESS_WHISPERS_LENGTH 60   /*!< Careless Whispers melody length */

/**
 * @brief Careless Whispers notes.
 *
 * This array contains the frequencies of the notes for the Careless Whispers song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double careless_whispers_notes[CARELESS_WHISPERS_LENGTH] = {
    SILENCE, DOs5, 
    DOs6, SI5, FAs5, RE5, DOs6, SI5, FAs5, RE5, 
    LA5, SOL5, RE5, SI4, LA5, SOL5, RE5, 
    SOL5, FAs5, RE5, SI4, SOL4, LA4, 
    FAs4, SOL4, LA4, SI4, DOs5, RE5, MI5, FAs5, 
    DOs6, SI5, FAs5, RE5, DO6, SI5, FAs5, RE5, 
    LA5, SOL5, RE5, SI4, LA5, SOL5, RE5, 
    SOL5, FAs5, RE5, SI4, SOL4, LA4, 
    FAs4, SOL4, LA4, SI4, DOs5, RE5, MI5, FAs5};

/**
 * @brief Careless Whispers durations in miliseconds.
 * 
 * This array contains the duration of each note in the Careless Whispers song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t careless_whispers_durations[CARELESS_WHISPERS_LENGTH] = {
    100, 280, 
    280, 140, 280, 280, 420, 140, 280, 420, 
    280, 140, 280, 280, 420, 140, 700, 
    280, 140, 280, 280, 1120, 140, 
    280, 280, 280, 280, 280, 280, 280, 280, 
    280, 140, 280, 280, 420, 140, 280, 420, 
    280, 140, 280, 280, 420, 140, 700, 
    280, 140, 280, 280, 1120, 140, 
    280, 280, 280, 280, 280, 280, 280, 280};

/**
 * @brief Careless Whispers struct.
 * 
 * This struct contains the information of the Careless Whispers.
 * It is used to play the melody using the buzzer.
 */
const melody_t careless_whispers = {.p_name = "Careless Whispers",
                               .p_notes = (double *)careless_whispers_notes,
                               .p_durations = (uint16_t *)careless_whispers_durations,
                               .melody_length = CARELESS_WHISPERS_LENGTH};
                               


// The Legend of Zelda Main Theme 

#define LEGEND_OF_ZELDA_MAIN_LENGTH 85   /*!< The Legend of Zelda Main Theme melody length */

/**
 * @brief The Legend of Zelda Main Theme notes.
 *
 * This array contains the frequencies of the notes for the The Legend of Zelda Main Theme song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double legend_of_zelda_main_notes[LEGEND_OF_ZELDA_MAIN_LENGTH] = {
    SILENCE, LA4, SILENCE, LA4, LA4, LA4, LA4,
    LA4, SOL4, LA4, SILENCE, LA4, LA4, LA4, LA4,
    LA4, SOL4, LA4, SILENCE, LA4, LA4, LA4, LA4,
    LA4, MI4, MI4, MI4, MI4, MI4, MI4, MI4, MI4, MI4, MI4, 
    LA4, MI4, LA4, LA4, SI4, DOs5, RE5, 
    MI5, SILENCE, MI5, MI5, FA5, SOL5, 
    LA5, SILENCE, LA5, LA5, SOL5, FA5,
    SOL5, FA5, MI5, MI5, 
    RE5, RE5, MI5, FA5, MI5, RE5, 
    DO5, DO5, RE5, MI5, RE5, DO5, 
    SI4, SI4, DOs5, REs5, FAs5, 
    MI5, MI4, MI4, MI4, MI4, MI4, MI4, MI4, MI4, MI4, MI4};

/**
 * @brief The Legend of Zelda Main Theme durations in miliseconds.
 * 
 * This array contains the duration of each note in the The Legend of Zelda Main Theme song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t legend_of_zelda_main_durations[LEGEND_OF_ZELDA_MAIN_LENGTH] = {
    100, 800, 267, 133, 133, 133, 134,
    267, 133, 400, 267, 133, 133, 133, 134,
    267, 133, 400, 267, 133, 133, 133, 134,
    200, 100, 100, 200, 100, 100, 200, 100, 100, 200, 200, 
    400, 600, 200, 100, 100, 100, 100, 
    800, 200, 200, 133, 133, 134,
    800, 200, 200, 133, 133, 134, 
    300, 100, 800, 400, 
    200, 100, 100, 800, 200, 200, 
    200, 100, 100, 800, 200, 200, 
    200, 100, 100, 800, 400, 
    200, 100, 100, 200, 100, 100, 200, 100, 100, 200, 200};

/**
 * @brief The Legend of Zelda Main Theme struct.
 * 
 * This struct contains the information of the The Legend of Zelda Main Theme.
 * It is used to play the melody using the buzzer.
 */
const melody_t legend_of_zelda_main = {.p_name = "The Legend of Zelda Main Theme",
                               .p_notes = (double *)legend_of_zelda_main_notes,
                               .p_durations = (uint16_t *)legend_of_zelda_main_durations,
                               .melody_length = LEGEND_OF_ZELDA_MAIN_LENGTH};

// IMPERIAL MARCH

#define IMPERIAL_MARCH_LENGTH 71   /*!< Imperial March melody length */

/**
 * @brief Imperial March notes.
 *
 * This array contains the frequencies of the notes for the Imperial March song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double imperial_march_notes[IMPERIAL_MARCH_LENGTH] = {
    SILENCE, SOL4, SOL4, SOL4, REs4, LAs4, 
    SOL4, REs4, LAs4, SOL4, 
    RE5, RE5, RE5, REs5, LAs4, 
    FAs4, REs4, LAs4, SOL4, 
    SOL5, SOL4, SOL4, SOL5, FAs5, FA5, 
    MI5, REs5, MI5, SILENCE, SOLs4, DOs5, DO5, SI4, 
    LAs4, LA4, LAs4, SILENCE, REs4, FAs4, REs4, FAs4, 
    LAs4, SOL4, LAs4, RE5, 
    SOL5, SOL4, SOL4, SOL5, FAs5, FA5, 
    MI5, REs5, MI5, SILENCE, SOLs4, DOs5, DO5, SI4, 
    LAs4, LA4, LAs4, SILENCE, REs4, FAs4, REs4, LAs4, 
    SOL4, REs4, LAs4, SOL4};

/**
 * @brief Imperial March durations in miliseconds.
 * 
 * This array contains the duration of each note in the Imperial March song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t imperial_march_durations[IMPERIAL_MARCH_LENGTH] = {
    100, 400, 400, 400, 300, 100, 
    400, 300, 100, 800, 
    400, 400, 400, 300, 100,
    400, 300, 100, 800, 
    400, 300, 100, 400, 300, 100, 
    100, 100, 200, 200, 200, 400, 300, 100,
    100, 100, 200, 200, 200, 400, 300, 100, 
    400, 300, 100, 800, 
    400, 300, 100, 400, 300, 100, 
    100, 100, 200, 200, 200, 400, 300, 100, 
    100, 100, 200, 200, 200, 400, 300, 100, 
    400, 300, 100, 800};

/**
 * @brief Imperial March struct.
 * 
 * This struct contains the information of the Imperial March.
 * It is used to play the melody using the buzzer.
 */
const melody_t imperial_march = {.p_name = "Imperial March",
                               .p_notes = (double *)imperial_march_notes,
                               .p_durations = (uint16_t *)imperial_march_durations,
                               .melody_length = IMPERIAL_MARCH_LENGTH};

// Mario Bros Main Theme 

#define MARIO_BROS_MAIN_LENGTH 192   /*!< Mario Bros Main Theme melody length */

/**
 * @brief Mario Bros Main Theme notes.
 *
 * This array contains the frequencies of the notes for the Mario Bros Main Theme song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double mario_bros_main_notes[MARIO_BROS_MAIN_LENGTH] = {
    SILENCE, MI5, MI5, SILENCE, MI5, SILENCE, DO5, MI5, 
    SOL5, SILENCE, SOL4, SILENCE, 
    DO5, SILENCE, SOL4, SILENCE, MI4, 
    SILENCE, LA4, SI4, LAs4, LA4, 
    SOL4, MI5, SOL5, LA5, FA5, SOL5, 
    SILENCE, MI5, DO5, RE5, SI4, SILENCE, 
    DO5, SILENCE, SOL4, SILENCE, MI4, 
    SILENCE, LA4, SI4, LAs4, LA4, 
    SOL4, MI5, SOL5, LA5, FA5, SOL5, 
    SILENCE, MI5, DO5, RE5, SI4, SILENCE, //55
    SILENCE, SOL5, FAs5, FA5, REs5, MI5, 
    SILENCE, SOLs4, LA4, DO5, SILENCE, LA4, DO5, RE5, 
    SILENCE, SOL5, FAs5, FA5, REs5, MI5, 
    SILENCE, DO6, DO6, DO6, SILENCE, 
    SILENCE, SOL5, FAs5, FA5, REs5, MI5, 
    SILENCE, SOLs4, LA4, DO5, SILENCE, LA4, DO5, RE5, 
    SILENCE, REs5, SILENCE, RE5, SILENCE, 
    DO5, SILENCE,
    SILENCE, SOL5, FAs5, FA5, REs5, MI5, 
    SILENCE, SOLs4, LA4, DO5, SILENCE, LA4, DO5, RE5, 
    SILENCE, SOL5, FAs5, FA5, REs5, MI5, 
    SILENCE, DO6, DO6, DO6, SILENCE, 
    SILENCE, SOL5, FAs5, FA5, REs5, MI5, 
    SILENCE, SOLs4, LA4, DO5, SILENCE, LA4, DO5, RE5, 
    SILENCE, REs5, SILENCE, RE5, SILENCE, 
    DO5, SILENCE, //147
    DO5, DO5, SILENCE, DO5, SILENCE, DO5, RE5, 
    MI5, DO5, SILENCE, LA4, SOL4, 
    DO5, DO5, SILENCE, DO5, SILENCE, DO5, RE5, MI5, 
    SILENCE, 
    DO5, DO5, SILENCE, DO5, SILENCE, DO5, RE5, 
    MI5, DO5, SILENCE, LA4, SOL4, 
    MI5, MI5, SILENCE, MI5, SILENCE, DO5, MI5, 
    SOL5, SILENCE, SOL4, SILENCE };

/**
 * @brief Mario Bros Main Theme durations in miliseconds.
 * 
 * This array contains the duration of each note in the Mario Bros Main Theme song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t mario_bros_main_durations[MARIO_BROS_MAIN_LENGTH] = {
    100, 150, 150, 150, 150, 150, 150, 300, 
    300, 300, 300, 300, 
    300, 150, 300, 150, 300, 
    150, 300, 300, 150, 300, 
    200, 200, 200, 300, 150, 150, 
    150, 300, 150, 150, 300, 150, 
    300, 150, 300, 150, 300, 
    150, 300, 300, 150, 300, 
    200, 200, 200, 300, 150, 150, 
    150, 300, 150, 150, 300, 150, //55
    300, 150, 150, 150, 300, 150, 
    150, 150, 150, 150, 150, 150, 150, 150, 
    300, 150, 150, 150, 300, 150, 
    150, 300, 150, 300, 300, 
    300, 150, 150, 150, 300, 150, 
    150, 150, 150, 150, 150, 150, 150, 150, 
    300, 300, 150, 300, 150, 
    300, 900, 
    300, 150, 150, 150, 300, 150, 
    150, 150, 150, 150, 150, 150, 150, 150, 
    300, 150, 150, 150, 300, 150, 
    150, 300, 150, 300, 300, 
    300, 150, 150, 150, 300, 150, 
    150, 150, 150, 150, 150, 150, 150, 150, 
    300, 300, 150, 300, 150, 
    300, 900, //147
    150, 150, 150, 150, 150, 150, 300, 
    150, 150, 150, 150, 600, 
    150, 150, 150, 150, 150, 150, 150, 150, 
    1200, 
    150, 150, 150, 150, 150, 150, 300, 
    150, 150, 150, 150, 600, 
    150, 150, 150, 150, 150, 150, 300, 
    300, 300, 300, 300 };

/**
 * @brief Mario Bros Main Theme struct.
 * 
 * This struct contains the information of the Mario Bros Main Theme.
 * It is used to play the melody using the buzzer.
 */
const melody_t mario_bros_main = {.p_name = "Mario Bros Main Theme",
                               .p_notes = (double *)mario_bros_main_notes,
                               .p_durations = (uint16_t *)mario_bros_main_durations,
                               .melody_length = MARIO_BROS_MAIN_LENGTH};


// Pokemon Main

#define POKEMON_MAIN_LENGTH 49   /*!< Pokemon Main melody length */

/**
 * @brief Pokemon Main notes.
 *
 * This array contains the frequencies of the notes for the Pokemon Main song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double pokemon_main_notes[POKEMON_MAIN_LENGTH] = {
    SILENCE, SOL4, SOL4, SILENCE, SOL4, SOL4, SOL4, 
    SOL4, SOL4, FA4, FA4, FA4, FA4, FA4, FAs4, 
    SOL4, SI4, RE5, 
    SILENCE, LA4, FA5, MI5, REs5, 
    RE5, FA4, MI4, REs4, 
    RE4, DO4, SI3, DO4, 
    SOL4, SI4, RE5, 
    SILENCE, DO5, LA4, DO5, 
    RE5, FA4, MI4, DO4, 
    RE4, SI3, DO4, RE4, 
    SOL4, SI4, RE5};

/**
 * @brief Pokemon Main durations in miliseconds.
 * 
 * This array contains the duration of each note in the Pokemon Main song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t pokemon_main_durations[POKEMON_MAIN_LENGTH] = {
    100, 400, 400, 200, 100, 100, 400, 
    400, 400, 133, 133, 134, 133, 133, 134, 
    600, 200, 800, 
    400, 400, 600, 100, 100, 
    800, 600, 100, 100, 
    800, 266, 267, 267, 
    600, 200, 800, 
    800, 266, 267, 267, 
    800, 266, 267, 267, 
    1000, 200, 200, 200, 
    600, 200, 800};

/**
 * @brief Pokemon Main struct.
 * 
 * This struct contains the information of the Pokemon Main.
 * It is used to play the melody using the buzzer.
 */
const melody_t pokemon_main = {.p_name = "Pokemon Main",
                               .p_notes = (double *)pokemon_main_notes,
                               .p_durations = (uint16_t *)pokemon_main_durations,
                               .melody_length = POKEMON_MAIN_LENGTH};

// Halloween Theme

#define HALLOWEEN_THEME_LENGTH 241   /*!< Halloween Theme melody length */

/**
 * @brief Halloween Theme notes.
 *
 * This array contains the frequencies of the notes for the Halloween Theme song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double halloween_theme_notes[HALLOWEEN_THEME_LENGTH] = {
    SILENCE, DOs6, FAs5, FAs5, DOs6, FAs5, FAs5, DOs6, FAs5, RE6, FAs5, 
    DOs6, FAs5, FAs5, DOs6, FAs5, FAs5, DOs6, FAs5, RE6, FAs5, 
    DOs6, FAs5, FAs5, DOs6, FAs5, FAs5, DOs6, FAs5, RE6, FAs5, 
    DOs6, FAs5, FAs5, DOs6, FAs5, FAs5, DOs6, FAs5, RE6, FAs5, 
    DOs6, FAs5, FAs5, DOs6, FAs5, FAs5, DOs6, FAs5, RE6, FAs5, 
    DOs6, FAs5, FAs5, DOs6, FAs5, FAs5, DOs6, FAs5, RE6, FAs5, 
    DO6, FA5, FA5, DO6, FA5, FA5, DO6, FA5, DOs6, FA5, 
    DO6, FA5, FA5, DO6, FA5, FA5, DO6, FA5, DOs6, FA5, 
    DOs6, FAs5, FAs5, DOs6, FAs5, FAs5, DOs6, FAs5, RE6, FAs5, 
    DOs6, FAs5, FAs5, DOs6, FAs5, FAs5, DOs6, FAs5, RE6, FAs5, 
    DO6, FA5, FA5, DO6, FA5, FA5, DO6, FA5, DOs6, FA5, 
    DO6, FA5, FA5, DO6, FA5, FA5, DO6, FA5, DOs6, FA5, 
    SI5, MI5, MI5, SI5, MI5, MI5, SI5, MI5, DO6, MI5, 
    SI5, MI5, MI5, SI5, MI5, MI5, SI5, MI5, DO6, MI5, 
    LAs5, REs5, REs5, LAs5, REs5, REs5, LAs5, REs5, SI5, REs5, 
    LAs5, REs5, REs5, LAs5, REs5, REs5, LAs5, REs5, SI5, REs5, 
    SI5, MI5, MI5, SI5, MI5, MI5, SI5, MI5, DO6, MI5, 
    SI5, MI5, MI5, SI5, MI5, MI5, SI5, MI5, DO6, MI5, 
    LAs5, REs5, REs5, LAs5, REs5, REs5, LAs5, REs5, SI5, REs5, 
    LAs5, REs5, REs5, LAs5, REs5, REs5, LAs5, REs5, SI5, REs5, 
    FAs5, SI5, SI5, FAs5, SI5, SI5, FAs5, SI5, SOL5, SI5, 
    FAs5, SI5, SI5, FAs5, SI5, SI5, FAs5, SI5, SOL5, SI5, 
    FAs5, SI5, SI5, FAs5, SI5, SI5, FAs5, SI5, SOL5, SI5, 
    FAs5, SI5, SI5, FAs5, SI5, SI5, FAs5, SI5, SOL5, SI5};

/**
 * @brief Halloween Theme durations in miliseconds.
 * 
 * This array contains the duration of each note in the Halloween Theme song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t halloween_theme_durations[HALLOWEEN_THEME_LENGTH] = {
    100, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200};

/**
 * @brief Halloween Theme struct.
 * 
 * This struct contains the information of the Halloween Theme.
 * It is used to play the melody using the buzzer.
 */
const melody_t halloween_theme = {.p_name = "Halloween Theme",
                               .p_notes = (double *)halloween_theme_notes,
                               .p_durations = (uint16_t *)halloween_theme_durations,
                               .melody_length = HALLOWEEN_THEME_LENGTH};