#pragma once
#include "Timers_decl.hpp"

#include "Strings.hpp"

namespace MyUtils::Timers {
  
#if(defined(myUtils_ENABLE_TIMERS) && myUtils_ENABLE_TIMERS)
  
inline void TimerRegistry::addTimer(const Timer& timer) {
  std::lock_guard<std::mutex> lock(mutex_);
  std::string name = timer.name_;
  auto it = timers_.find(name);
  if (it == timers_.end()) {
    timersOrdered_.push_back(name);
    timers_[name] = timer; // this does copy
  }
  else {
    timers_[name].timerVal_secDouble_ += timer.timerVal_secDouble_; // direct use for efficiency?
  }
}

inline std::string TimerRegistry::timingReportStr(int levelizeN, bool sortByStartElseFinish) {
  std::string out = "==== Timing Report ====\n";
  double totalTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-totalStart_).count();
  std::string out2 = "Timer name | Timer value [s] | Share of registry total [%] | Start of timer [s]\n";
  
  out2 += "* "+registryName_+" | "+std::to_string(totalTime)+" | "+"100"+" | "+"0 by definition"+"\n";
  
  if(sortByStartElseFinish)
    std::sort(timersOrdered_.raw().begin(), timersOrdered_.raw().end(), [&](const std::string& a, const std::string& b) {
      return timers_.at(a).start_ < timers_.at(b).start_;
    });
  
  FOR(i, timersOrdered_.size()) {
    const std::string& name = timersOrdered_(i);
    const Timer& timer = timers_.at(name);
    double timerVal = timer.getTimerVal_secDouble();
    double shareOfTotal = timerVal/totalTime;
    out2 += name+" | "+std::to_string(timerVal)+" | "+std::to_string(shareOfTotal*100)+" | "+std::to_string(std::chrono::duration<double>(timer.start_-totalStart_).count())+"\n";
  }

  return Strings::levelizeString(out + Strings::alignStringAt(out2, "|"), levelizeN);
}

#else

inline std::string TimerRegistry::timingReportStr() const noexcept {
  std::string out = "==== Timing Report : Timers are off (myUtils_ENABLE_TIMERS == false) ====\n";
  out += "Registry name: "+registryName_+"\n";
  double totalTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-totalStart_).count();
  out += "Total registry time | " + std::to_string(totalTime) + "s\n";
  return Strings::levelizeString(out, 1);
}

#endif

}
