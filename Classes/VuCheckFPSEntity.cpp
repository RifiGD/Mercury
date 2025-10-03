/* pseudo-code for now, not meant to be used 
or compiled at all */


/* VuCheckFPSEntity::Trigger(VuParams const&) */

undefined8 VuCheckFPSEntity::Trigger(VuParams *param_1)

{
  int AvgFPS;
  long *plugPtr;
  char *plugName;
  undefined1 argsBuffer [256];
  undefined4 emptyVar;
  long pointSoftwareThread;
  long softwareThreadID;
  
  softwareThreadID = tpidr_el0;
  pointSoftwareThread = *(long *)(softwareThreadID + 0x28);
  AvgFPS = VuTickManager::calcAvgFps(VuTickManager::mpInterface);
  if (AvgFPS < *(int *)(param_1 + 0xc0)) {
    plugName = "Fail";
  }
  else {
    plugName = "Pass";
  }
  plugPtr = (long *)VuScriptComponent::getPlug(*(VuScriptComponent **)(param_1 + 0xb8),plugName);
  emptyVar = 0;
  (**(code **)(*plugPtr + 0x18))(plugPtr,argsBuffer);
  if (*(long *)(softwareThreadID + 0x28) == pointSoftwareThread) {
    return 0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
