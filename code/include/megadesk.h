#pragma once

enum class State : byte
{
  OFF,
  STARTING,
  UP,
  DOWN,
  STOPPING1,
  STOPPING2,
  STOPPING3,
  STOPPING4,
  STARTING_RECAL,
  RECAL,
  END_RECAL
};

enum class Command : byte
{
  NONE,
  UP,
  DOWN,
};

enum class Button : byte
{
  NONE,
  UP,
  DOWN,
  BOTH,
};

// class to reset via watchdog timer,
// then disable watchdog again during init
class softReset {
  public:
    softReset();
    static void Reset();
};

// serial markers and operations
const char rxMarker          = '<'; // start marker for comms coming to desk (Rx)
const char command_increase  = '+';
const char command_decrease  = '-';
const char command_absolute  = '=';
const char command_save      = 'S'; // up-button slots
const char command_save_down = 's'; // down-button slots
const char command_load      = 'L'; // up-button slots
const char command_load_down = 'l'; // down-button slots
const char command_write     = 'W';
const char command_read      = 'R';
const char command_current   = 'C'; // report current height
const char command_tone      = 'T';

// responses only..
const char txMarker          = '>'; // default start marker from desk (Tx)
const char response_error    = 'E'; // indicates an error
const char response_calibration = 'X'; // indicates calibration is starting

// error markers
const char lateMarker        = '!'; // when reporting delayUntil was late
const char bootfailMarker    = '*'; // when linInit fails to communicate
const char badPID8Marker     = '8'; // when pid8 fails to respond
const char badPID9Marker     = '9'; // when pid9 fails to respond
const char DriftMarker       = 'D'; // when pid8 and pid9 report different positions

// idle markers
const char idleMarker        = 'i'; // indicates the type of idle packet
const char response_stop     = 's'; // during stop idle
const char response_off      = 'o'; // when starting from off-state

// debugheight markers
const char response_up       = '^'; // raising to targetheight
const char response_down     = 'v'; // lowering to targetheight
const char response_halt     = '~'; // halt moving! aim for targetheight

void playTone(uint16_t freq, uint16_t duration);
void beep(uint16_t freq, byte count=1);

void delayUntil(uint16_t milliSeconds);

void linInit();
uint8_t linBurst();

void sendInitPacket(byte a1 = 255, byte a2 = 255, byte a3 = 255, byte a4 = 255);
byte recvInitPacket(byte array[]);

void toggleDangerMinHeight();
void toggleMinHeight();
void toggleMaxHeight();
void toggleBothMode();
void toggleFeedback();

// serial functions
void writeSerial(byte operation, uint16_t position, uint8_t push_addr = 0, byte marker = txMarker);
void parseData(byte command, uint16_t position, uint8_t push_addr);

// eeprom
void initAndReadEEPROM(bool force);
uint16_t eepromGet16( int idx );
void eepromPut16( int idx, uint16_t val );

uint16_t loadMemory(uint8_t memorySlot);
void saveMemory(uint8_t memorySlot, uint16_t value);
