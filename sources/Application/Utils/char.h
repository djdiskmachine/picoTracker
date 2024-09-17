#ifndef _CHAR_H_
#define _CHAR_H_

#include "Foundation/Types/Types.h"
#include <string.h>

extern char h2c__[16];
extern const char *notes__[12];

inline void hex2char(const unsigned char c, char *s) {
  char *dest__ = s;
  *dest__++ = h2c__[(c & 0xF0) >> 4];
  *dest__++ = h2c__[c & 0x0F];
  *dest__ = 0;
}

inline void hexshort2char(const ushort c, char *s) {
  char *dest__ = s;
  *dest__++ = h2c__[(c & 0xF000) >> 12];
  *dest__++ = h2c__[(c & 0xF00) >> 8];
  *dest__++ = h2c__[(c & 0xF0) >> 4];
  *dest__++ = h2c__[c & 0x0F];
  *dest__ = 0;
}

#define c2h__(c) (c < 'A' ? c - '0' : c - 'A' + 10)

inline void char2hex(const char *s, unsigned char *c) {
  const char *src__ = s;
  unsigned char b1 = (c2h__(src__[0])) << 4;
  unsigned char b2 = c2h__(src__[1]);
  *c = b1 + b2;
}

inline void note2char(unsigned char d, char *s) {
  int oct = d / 12 - 2;
  int note = d % 12;
  strcpy(s, notes__[note]);
  if (oct < 0) {
    s[2] = '-';
    oct = -oct;
  } else {
    s[2] = ' ';
  }
  s[3] = '0' + oct;
};

inline void note2visualizer(unsigned char d, char *s) {
  int note = d % 12;
  strcpy(s, notes__[note]);
  s[2] = '\0'; // sloppy, can we make the array shorter?
  s[3] = '\0'; // sloppy, can we make the array shorter?
};

inline void oct2visualizer(unsigned char d, char *s) {
  int oct = d / 12 - 2;
  if (oct < 0) {
    s[0] = '-';
    oct = -oct;
  } else {
    s[0] = ' ';
  }
  s[1] = '0' + oct;
  s[2] = '\0'; // sloppy, can we make the array shorter?
  s[3] = '\0'; // sloppy, can we make the array shorter?
};

inline void fourCC2char(const FourCC f, char *s) {
  switch (f) {
  case 0:
    strcpy(s, "ARP"); // ARPG
    break;
  case 1:
    strcpy(s, "CHNL");
    break;
  case 2:
    strcpy(s, "CSH"); // CRSH
    break;
  case 3:
    strcpy(s, "CRSV");
    break;
  case 4:
    strcpy(s, "DLY"); // DLAY
    break;
  case 5:
    strcpy(s, "DSPL");
    break;
  case 6:
    strcpy(s, "END_");
    break;
  case 7:
    strcpy(s, "EVA_");
    break;
  case 8:
    strcpy(s, "EVB_");
    break;
  case 9:
    strcpy(s, "EVDN");
    break;
  case 10:
    strcpy(s, "EVLF");
    break;
  case 11:
    strcpy(s, "EVLS");
    break;
  case 12:
    strcpy(s, "EVRS");
    break;
  case 13:
    strcpy(s, "EVRT");
    break;
  case 14:
    strcpy(s, "EVST");
    break;
  case 15:
    strcpy(s, "EVUP");
    break;
  case 16:
    strcpy(s, "FBAM");
    break;
  case 19:
    strcpy(s, "FBTU");
    break;
  case 20:
    strcpy(s, "FCT"); // FCUT
    break;
  case 21:
    strcpy(s, "FIMO");
    break;
  case 22:
    strcpy(s, "FLT"); // FLTR
    break;
  case 23:
    strcpy(s, "FMIX");
    break;
  case 24:
    strcpy(s, "FNTN");
    break;
  case 25:
    strcpy(s, "FRS"); // FRES
    break;
  case 26:
    strcpy(s, "GRV"); // GROV
    break;
  case 27:
    strcpy(s, "HOP");
    break;
  case 28:
    strcpy(s, "INTP");
    break;
  case 29:
    strcpy(s, "IRT"); // IRTG
    break;
  case 30:
    strcpy(s, "KIL"); // KILL
    break;
  case 31:
    strcpy(s, "LEG"); // LEGA
    break;
  case 32:
    strcpy(s, "LENG");
    break;
  case 33:
    strcpy(s, "LLEN");
    break;
  case 34:
    strcpy(s, "LMOD");
    break;
  case 35:
    strcpy(s, "LOAD");
    break;
  case 36:
    strcpy(s, "LOF"); // LPOF
    break;
  case 37:
    strcpy(s, "LSTA");
    break;
  case 38:
    strcpy(s, "MCC"); // MDCC
    break;
  case 39:
    strcpy(s, "MPC"); // MDPG
    break;
  case 40:
    strcpy(s, "MIDI");
    break;
  case 41:
    strcpy(s, "MSTR");
    break;
  case 42:
    strcpy(s, "PAN");
    break;
  case 43:
    strcpy(s, "PAN_");
    break;
  case 44:
    strcpy(s, "PFT"); // PFIN
    break;
  case 45:
    strcpy(s, "---"); // ----
    break;
  case 46:
    strcpy(s, "POF"); // PLOF
    break;
  case 47:
    strcpy(s, "PRGI");
    break;
  case 48:
    strcpy(s, "PSL"); // PTCH
    break;
  case 49:
    strcpy(s, "PURG");
    break;
  case 51:
    strcpy(s, "ROOT");
    break;
  case 52:
    strcpy(s, "RTG"); // RTRG
    break;
  case 53:
    strcpy(s, "SAVE");
    break;
  case 54:
    strcpy(s, "SMPL");
    break;
  case 55:
    strcpy(s, "STP"); // STOP
    break;
  case 56:
    strcpy(s, "STRT");
    break;
  case 57:
    strcpy(s, "SVPS");
    break;
  case 58:
    strcpy(s, "TBL"); // TABL
    break;
  case 59:
    strcpy(s, "TBED");
    break;
  case 60:
    strcpy(s, "TBLA");
    break;
  case 61:
    strcpy(s, "TEMP");
    break;
  case 62:
    strcpy(s, "TPO"); // TMPO
    break;
  case 63:
    strcpy(s, "TRSP");
    break;
  case 64:
    strcpy(s, "TSQR");
    break;
  case 65:
    strcpy(s, "TTAP");
    break;
  case 66:
    strcpy(s, "VEL"); // VELM - midi velocity
    break;
  case 67:
    strcpy(s, "VLDN");
    break;
  case 68:
    strcpy(s, "VLUP");
    break;
  case 69:
    strcpy(s, "VOL"); // VOLM
    break;
  case 70:
    strcpy(s, "WRAP");
    break;
  case 71:
    strcpy(s, "DPW ");
    break;
  case 72:
    strcpy(s, "D1WF");
    break;
  case 73:
    strcpy(s, "D2WF");
    break;
  case 74:
    strcpy(s, "D3WF");
    break;
  case 75:
    strcpy(s, "DSYN");
    break;
  case 76:
    strcpy(s, "DRNG");
    break;
  case 77:
    strcpy(s, "DADS");
    break;
  case 78:
    strcpy(s, "DFON");
    break;
  case 79:
    strcpy(s, "D1FC");
    break;
  case 80:
    strcpy(s, "D1RS");
    break;
  case 81:
    strcpy(s, "D1FM");
    break;
  case 82:
    strcpy(s, "D1VL");
    break;
  case 83:
    strcpy(s, "D2FC");
    break;
  case 84:
    strcpy(s, "D2RS");
    break;
  case 85:
    strcpy(s, "D2FM");
    break;
  case 86:
    strcpy(s, "D2VL");
    break;
  case 87:
    strcpy(s, "D3FC");
    break;
  case 88:
    strcpy(s, "D3RS");
    break;
  case 89:
    strcpy(s, "D3FM");
    break;
  case 90:
    strcpy(s, "D3VL");
    break;
  case 91:
    strcpy(s, "D3OF");
    break;
  case 92:
    strcpy(s, "GOF"); // I_CMD_GTOF
  case 93:
    strcpy(s, "SHPE");
    break;
  case 94:
    strcpy(s, "TIMB");
    break;
  case 95:
    strcpy(s, "COLR");
    break;
  case 96:
    strcpy(s, "ATCK");
    break;
  case 97:
    strcpy(s, "DECY");
    break;
  case 98:
    strcpy(s, "SIGN");
    break;
  case 99:
    strcpy(s, "PANM");
    break;
  case 100:
    strcpy(s, "RNDP");
    break;
  case 101:
    strcpy(s, "NEWP");
    break;
  case 102:
    strcpy(s, "PRNM");
    break;
  case 103:
    strcpy(s, "FGCL");
    break;
  case 104:
    strcpy(s, "BGCL");
    break;
  case 105:
    strcpy(s, "H1CL");
    break;
  case 106:
    strcpy(s, "H2CL");
    break;
  case 107:
    strcpy(s, "CNCL");
    break;
  case 108:
    strcpy(s, "CRCL");
    break;
  case 109:
    strcpy(s, "IFCL");
    break;
  case 110:
    strcpy(s, "WNCL");
    break;
  case 111:
    strcpy(s, "ERCL");
    break;
  case 112:
    strcpy(s, "MIDD");
    break;
  case 113:
    strcpy(s, "MIDS");
    break;
  }
};
#endif
