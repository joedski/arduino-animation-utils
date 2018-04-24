#include "JoeDSki_AnimationProgressTimingModel.h"


int32_t speculativeProgressForTimeDelta(struct JoeDSki_AnimationProgressTimingModel &model, uint32_t timeDelta);


JoeDSki_AnimationProgressTimingModel::JoeDSki_AnimationProgressTimingModel(
  uint32_t normalDuration,
  int16_t rate100 = 100,
  uint16_t progress = 0
)
  : normalDuration(normalDuration)
  , rate100(rate100)
  , progress(progress)
{}

void JoeDSki_AnimationProgressTimingModel::increment(uint32_t timeDelta) {
  // Skip immediately on some cases.
  // Assumes timeDelta is left unsigned and > 0.
  if (
    (rate100 > 0 && progress == ANIMATION_PROGRESS_MAX)
    || (rate100 < 0 && progress == 0)
  ) return;

  int32_t nextProgressSpeculative = speculativeProgressForTimeDelta(*this, timeDelta);

  // This is the non-cyclic version, so we need to stop at either end.
  if (nextProgressSpeculative > ANIMATION_PROGRESS_MAX) {
    // NOTE: Non-cyclic progress _can_ be the max value!
    progress = ANIMATION_PROGRESS_MAX;
  }
  else if (nextProgressSpeculative < 0) {
    progress = 0;
  }
  else {
    progress = nextProgressSpeculative;
  }
}

void JoeDSki_AnimationProgressTimingModel::incrementCyclic(uint32_t timeDelta) {
  int32_t nextProgressSpeculative = speculativeProgressForTimeDelta(*this, timeDelta);

  // Put things into positive territory before cycling via mod.
  if (nextProgressSpeculative < 0) {
    int32_t howFarDown = (int32_t)((nextProgressSpeculative * -1) / ANIMATION_PROGRESS_MAX);
    // Add one to put it into positive territory.
    nextProgressSpeculative += ANIMATION_PROGRESS_MAX * (howFarDown + 1);
  }

  progress = nextProgressSpeculative % ANIMATION_PROGRESS_MAX;
}


/**
 * Calculates the speculative next progress for a given time delta,
 * upgrading progress to an int32_t (signed!) to account for over/underflows.
 */
int32_t speculativeProgressForTimeDelta(struct JoeDSki_AnimationProgressTimingModel &model, uint32_t timeDelta) {
  int16_t normalProgressIcrement = (int16_t)(ANIMATION_PROGRESS_MAX * timeDelta / model.normalDuration);
  int32_t progressIncrement = (
    (int32_t)normalProgressIcrement
    * (int32_t)model.rate100
    / 100
  );
  int32_t speculativeProgress = (int32_t)(model.progress) + progressIncrement;

  return speculativeProgress;
}
