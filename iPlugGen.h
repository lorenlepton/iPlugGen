#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "gen_exported.h"
#include "gen_dsp/genlib.h"

const int kNumPresets = 4;

enum EParams
{
  fb = 0,
  centre = 0,
  depth = 0,
  rate = 0,
  kNumParams
};

using namespace iplug;
using namespace igraphics;
using namespace gen_exported;

class iPlugGen final : public Plugin
{
public:
  iPlugGen(const InstanceInfo& info);
//  ~IPlugGen();

#if IPLUG_DSP // http://bit.ly/2S64BDd
  void OnParamChange(int paramIdx) override;
  void OnReset() override;
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;

private:
  CommonState *gen;
#endif
};
