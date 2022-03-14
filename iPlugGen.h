#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "gen_exported.h"

const int kNumPresets = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

using namespace iplug;
using namespace igraphics;

class iPlugGen final : public Plugin
{
public:
  iPlugGen(const InstanceInfo& info);
  
  CommonState *gen;

#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
#endif
};
