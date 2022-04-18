#include "main.h"

#define LASER_SIZE 155
#define ENEMIES_SIZE 155

short laserY[LASER_SIZE] = {};
short enemiesY[ENEMIES_SIZE] = {};
volatile short shipY;

void resetGame() {
    for (short & i : laserY) {
        i = -1;
    }
    for (short & i : enemiesY) {
        i = -1;
    }
    shipY = VGAX_HEIGHT/2;
}

__attribute__((unused)) void setup() {
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    resetGame();
    static const char str0[] PROGMEM="Syncing with VGA...";
    VGAXUA::begin();
    VGAXUA::setExtendedColorsMask(0);
    VGAXUA::clear(1);
    VGAXUA::printPROGMEM((byte*)fnt_ufont_data, FNT_UFONT_SYMBOLS_COUNT, FNT_UFONT_HEIGHT, 3, 1, str0, 30, VGAX_WIDTH/2+10, 0);
    for (int i = 0; i < 100; i++)
        VGAXUA::delay(10);
}

void gameOver() {
    VGAXUA::clear(1);
    static const char str1[] PROGMEM="GAME OVER!";
    VGAXUA::printPROGMEM((byte*)fnt_ufont_data, FNT_UFONT_SYMBOLS_COUNT, FNT_UFONT_HEIGHT, 3, 1, str1, 30, VGAX_WIDTH/2+20, 0);
    VGAXUA::delay(1000);
    resetGame();
}

int frame = 0;

__attribute__((unused)) void loop() {
    if (digitalRead(4)) shipY+=2;
    if (digitalRead(5)) shipY-=2;

    if (shipY <= 0) shipY = 10;
    if (shipY >= VGAX_HEIGHT) shipY = VGAX_HEIGHT-10;

    VGAXUA::clear(0);

    if (frame == 0) {

        if (VGAXUA::rand() % 2 == 0) {
            if (VGAXUA::rand() % 2 == 0) {
                enemiesY[ENEMIES_SIZE - 1] = (short) (VGAXUA::rand() % ((VGAX_HEIGHT / 8 * 7 - VGAX_HEIGHT / 8) + 1) +
                                                      VGAX_HEIGHT / 8);
            }
        }

        for (int j = 0; j < ENEMIES_SIZE - 1; j++) {
            enemiesY[j] = enemiesY[j + 1];
        }

        enemiesY[ENEMIES_SIZE - 1] = -1;
    }

    frame++;
    if (frame>=2) frame = 0;

    for (int i = LASER_SIZE - 1; i > 0; i--)
        laserY[i] = laserY[i - 1];
    laserY[0] = -1;

    VGAXUA::blitwmask((byte*)img_space_data, (byte*)mask_data, IMG_SPACE_WIDTH, IMG_SPACE_HEIGHT, 10, shipY);
    laserY[25] = shipY + 6;

    for (int i = 25; i < LASER_SIZE; i++) {
        if (laserY[i] != -1) {
            if (((frame % 2) ? i : i + 1) % 4 == 0) VGAXUA::putpixel(i, laserY[i], 1);
            if (enemiesY[i] == laserY[i] || enemiesY[i] == laserY[i]+1 || enemiesY[i] == laserY[i]-1 || enemiesY[i] == laserY[i]-2 || enemiesY[i] == laserY[i]+2) {
                enemiesY[i] = -1;
            }
        }
    }

    for (int i = 25; i < ENEMIES_SIZE; i++) {
        if (enemiesY[i] != -1) {
            if (i == 25) gameOver();
            VGAXUA::putpixel(i, enemiesY[i], 1);
            VGAXUA::putpixel(i+1, enemiesY[i]+1, 1);
            VGAXUA::putpixel(i+2, enemiesY[i]+2, 1);
            VGAXUA::putpixel(i-1, enemiesY[i]-1, 1);
            VGAXUA::putpixel(i-2, enemiesY[i]-2, 1);
            VGAXUA::putpixel(i-1, enemiesY[i]+1, 1);
            VGAXUA::putpixel(i-2, enemiesY[i]+2, 1);
            VGAXUA::putpixel(i+1, enemiesY[i]-1, 1);
            VGAXUA::putpixel(i+2, enemiesY[i]-2, 1);
        }
    }

    VGAXUA::delay(1);
}