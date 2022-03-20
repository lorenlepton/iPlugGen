#include "iPlugGen.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

iPlugGen::iPlugGen(const InstanceInfo& info) : Plugin(info, MakeConfig(num_params(), kNumPresets)){
  gen = (CommonState *)create(44100.f, DEFAULT_BLOCK_SIZE);
  
  for (int i = 0; i < num_params(); i++) {
    ParamInfo* param = gen->params+i;
    GetParam(i)->InitDouble(param->name, param->defaultvalue, param->outputmin, param->outputmax, 0.01, param->units);
  }

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    
    const IRECT bound = pGraphics->GetBounds();
    const IRECT cell = bound.GetGridCell(1, 1, 1);
    
    for (int i = 0; i < num_params(); i++) {
      ParamInfo* param = gen->params+i;
      pGraphics->AttachControl(new IVKnobControl(cell.GetGridCell(i, 1, 4), i, param->name));
    }
  };
#endif
}

#if IPLUG_DSP
void iPlugGen::ProcessBlock(sample** inputs, sample** outputs, int nFrames){
  perform(gen, inputs, num_inputs(), outputs, num_outputs(), nFrames);
}
#endif

void iPlugGen::OnReset(){
  gen->sr = GetSampleRate();
  reset(gen);
}

void iPlugGen::OnParamChange(int paramIdx){
  setparameter(gen, paramIdx, GetParam(paramIdx)->Value(), 0);
}
