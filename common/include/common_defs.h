#pragma once

#include <windows.h>
#include <iterator>
#include <limits>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

typedef __int8  int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;

typedef unsigned __int8  uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

#if !( defined( FCCB ) && defined( FOURCC ) && defined( FRCC64 ) )
#define FCCB(B)								( ( B ) << 8 )
#define FOURCC(B1,B2,B3,B4)					( (uint32_t)B1 | FCCB( B2 | FCCB( B3 | FCCB( B4 ) ) ) )
#define FRCC64(B1,B2,B3,B4,B5,B6,B7,B8)		( ( (uint64_t)FOURCC( (B5), (B6), (B7), (B8) ) << 32 ) | FOURCC( (B1), (B2), (B3), (B4) ) )
#endif
