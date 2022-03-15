#include "iPlugGen.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "gen_dsp/genlib.h"

iPlugGen::iPlugGen(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets)){
  gen = (CommonState *)create(44100.f, DEFAULT_BLOCK_SIZE);
  
//  const float depth = create("m_depth_4", DEFAULT);
  
  for (int i = 0; i< num_params(); i++) {
    ParamInfo* p = gen->params+i;
    
    GetParam(rate)->InitDouble("rate", 0.1, 0.f, 5.f, 0.01);
//    GetParam(i)->InitDouble(p->name, p->defaultvalue, p->outputmin, p->outputmax, 0.00001, p->units);
//    GetParam(i)->InitDouble(<#const char *name#>, <#double defaultVal#>, <#double minVal#>, <#double maxVal#>, <#double step#>)
//    setparameter(gen, <#long index#>, <#t_param value#>, <#void *ref#>)
  }
  
//  GetParam(gen->params->name = "depth");
//  GetParam(depth)->InitDouble("depth", 100.f, 0.f, 300.f, 0.01);
//  GetParam(rate)->InitDouble("rate", 0.1, 0.f, 5.f, 0.01);
//  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");
//  GetParam(gen->params)->InitDouble("Gain", 0., 0., 300.0, 0.01, "%");

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();
//    pGraphics->AttachControl(new ITextControl(b.GetMidVPadded(50), "Hello iPlug 2!", IText(50)));
//    pGraphics->AttachControl(new IVKnobControl(b.GetCentredInside(100).GetVShifted(-100), kGain));
    
//    const float ddepth = gen->params->defaultvalue;
    
//    pGraphics->AttachControl(new IVSliderControl(b.GetMidVPadded(50), depth));
//    pGraphics->AttachControl(new IVSliderControl(b.GetMidVPadded(50).GetFromLeft(100), rate));
  };
#endif
}

#if IPLUG_DSP
void iPlugGen::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
//  float ddepth = gen->params->defaultvalue;
//  ddepth = GetParam(depth)->Value();
  
//  float rrate = gen->params->name = "rate";
//  rrate = GetParam(rate)->Value();
  
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
    for (int c = 0; c < nChans; c++) {
//      outputs[c][s] = inputs[c][s] * gain;
      perform(gen, inputs, num_inputs(), outputs, num_outputs(), nFrames);
    }
  }
}
#endif

void iPlugGen::OnReset(){

  gen->sr = GetSampleRate();
  reset(gen);
}


void iPlugGen::OnParamChange(int paramIdx)
{
  setparameter(gen, paramIdx, GetParam(paramIdx)->Value(), 0);
}
