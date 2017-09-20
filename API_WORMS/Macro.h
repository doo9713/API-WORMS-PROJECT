#pragma once

#define SINGLE(type) (**type::Inst())
#define OBJ SINGLE(CObjList)
#define TIME SINGLE(CTimeManager)
#define KEY SINGLE(CKeyManager)

#define FRAMETIME 0.016667