#include <stdint.h>

#include "flash.h"

#define FLASH_BASE          0x40023C00UL

#define FLASH_KEYR          (*(volatile uint32_t *)(FLASH_BASE + 0x04))
#define FLASH_SR            (*(volatile uint32_t *)(FLASH_BASE + 0x0C))
#define FLASH_CR            (*(volatile uint32_t *)(FLASH_BASE + 0x10))

#define FLASH_KEY1          0x45670123UL
#define FLASH_KEY2          0xCDEF89ABUL

#define FLASH_SR_EOP        (1U << 0)
#define FLASH_SR_OPERR      (1U << 1)
#define FLASH_SR_WRPERR     (1U << 4)
#define FLASH_SR_PGAERR     (1U << 5)
#define FLASH_SR_PGPERR     (1U << 6)
#define FLASH_SR_PGSERR     (1U << 7)
#define FLASH_SR_RDERR      (1U << 8)
#define FLASH_SR_BSY        (1U << 16)

#define FLASH_CR_SER        (1U << 1)
#define FLASH_CR_SNB_MASK   (0xFU << 3)

#define FLASH_CR_PSIZE_MASK (3U << 8)
#define FLASH_CR_PSIZE_X32  (2U << 8)

#define FLASH_CR_STRT       (1U << 16)
#define FLASH_CR_LOCK       (1UL << 31)

#define FLASH_ERROR_MASK \
    (FLASH_SR_OPERR  | \
     FLASH_SR_WRPERR | \
     FLASH_SR_PGAERR | \
     FLASH_SR_PGPERR | \
     FLASH_SR_PGSERR | \
     FLASH_SR_RDERR)

static void flash_wait(void)
{
    while (FLASH_SR & FLASH_SR_BSY) {
    }
}

static void flash_unlock(void)
{
    if (FLASH_CR & FLASH_CR_LOCK) {
        FLASH_KEYR = FLASH_KEY1;
        FLASH_KEYR = FLASH_KEY2;
    }
}

static void flash_lock(void)
{
    FLASH_CR |= FLASH_CR_LOCK;
}

static void flash_clear_status(void)
{
    /*
     * FLASH_SR status/error flags are cleared by
     * writing a 1 to them.
     */
    FLASH_SR =
        FLASH_SR_EOP |
        FLASH_ERROR_MASK;
}

static int flash_erase_sector(uint32_t sector)
{
    flash_wait();

    flash_clear_status();

    /*
     * Configure sector erase.
     *
     * PSIZE = x32 because the Nucleo normally runs at ~3.3 V.
     */
    FLASH_CR &= ~(FLASH_CR_SNB_MASK |
                  FLASH_CR_PSIZE_MASK);

    FLASH_CR |= FLASH_CR_SER;
    FLASH_CR |= (sector << 3);
    FLASH_CR |= FLASH_CR_PSIZE_X32;

    /*
     * Start the erase operation.
     */
    FLASH_CR |= FLASH_CR_STRT;

    flash_wait();

    /*
     * Return the control register to a neutral state.
     */
    FLASH_CR &= ~FLASH_CR_SER;
    FLASH_CR &= ~FLASH_CR_SNB_MASK;

    if (FLASH_SR & FLASH_ERROR_MASK) {
        return -1;
    }

    return 0;
}

int flash_erase_application(void)
{
    flash_unlock();

    /*
     * Application occupies sectors 2 through 7.
     *
     * NEVER erase sectors 0 or 1 here.
     */
    for (uint32_t sector = 2; sector <= 7; sector++) {
        if (flash_erase_sector(sector) != 0) {
            flash_lock();
            return -1;
        }
    }

    flash_lock();

    return 0;
}