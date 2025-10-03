/* VuCheckVersionEntity class*/
/*Mousebot - Vector Engine*/
/* pseudo-code, not meant to be used 
or compiled at all */

/* VuCheckVersionEntity::Check(VuParams const&) */

undefined8 VuCheckVersionEntity::Check(VuParams *params)

{
  int cmpResult;
  char *buildVersionStr;
  VuScriptComponent *scriptComponent;
  long *plug;
  uint year;
  uint month;
  uint day;
  undefined1 argsBuffer [256];
  undefined4 emptyVar;
  long pointSoftwareThread;
  long softwareThreadID;
  VuParams *targetVersionPtr;
  
  softwareThreadID = tpidr_el0;
  pointSoftwareThread = *(long *)(softwareThreadID + 0x28);
  VuTimeUtil::getCompileTime((VuTimeStruct *)&year);
  buildVersionStr =
       (char *)VuStringUtil::format("%04d.%02d.%02d",(ulong)year,(ulong)month,(ulong)day);
  targetVersionPtr = params + 0xc1;
  if (((byte)params[0xc0] & 1) != 0) {
    targetVersionPtr = *(VuParams **)(params + 0xd0);
  }
  cmpResult = VuStringUtil::compareVersions(buildVersionStr,(char *)targetVersionPtr);
  if (cmpResult < 1) {
    scriptComponent = *(VuScriptComponent **)(params + 0xb8);
    if (cmpResult < 0) {
      buildVersionStr = "Older";
    }
    else {
      buildVersionStr = "Equal";
    }
  }
  else {
    scriptComponent = *(VuScriptComponent **)(params + 0xb8);
    buildVersionStr = "Newer";
  }
  plug = (long *)VuScriptComponent::getPlug(scriptComponent,buildVersionStr);
  emptyVar = 0;
  (**(code **)(*plug + 0x18))(plug,argsBuffer);
  if (*(long *)(softwareThreadID + 0x28) == pointSoftwareThread) {
    return 0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
