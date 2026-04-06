ParameterController 

    KnobComponent* ptrToParameterKnob
    mode: =, <, >, gest, if ax++ then gain++, 
    mapping: ax=0 == gain=-60.0f, ax==180, gain==0
    click and drag onto parameter to link


should obj{EffectComponent,ParameterController}
or obj{EffectComponent} --link-- obj{ParameterController}
or obj{EffectComponent} owns child{ParameterController}
