#pragma once
#include "Core.hpp"

#include <chrono>
#include <string>
#include <mutex>
#include <unordered_map>

#include "Strings.hpp"

namespace MyUtils::Timer {

class Timer; // fwd decl

#if(MYUTILS_TIMERS_ON)
  
class TimerRegistry {
 public:
  TimerRegistry(const std::string& registryName)
  : registryName_(registryName) {};
 public:
  inline static TimerRegistry& globalInstance() {
    static TimerRegistry registry = TimerRegistry("Global Instance");
    return registry;
  }
  
  // for global tracking
  inline void start() {
    totalStart_ = std::chrono::high_resolution_clock::now();
  }

  // Usually called by the Timers themselves (automatically for ScopedTimer)
  inline void addTimer(const Timer& timer) {
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

  inline std::string timingReportStr(bool sortedByFinishElseStart = false) {
    std::string out = "==== Timing Report ====\n";
    double totalTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-totalStart_).count();
    std::string out2 = "Timer name | Timer value [s] | Share of registry total [%] | Start of timer [s]\n";
    
    out2 += "(Total) "+registryName_+" | "+st::to_string(totalTime)+" | "+"100"+" | "+"0 by definition"+"\n";
    
    if(sortByStartElseFinish)
      std::sort(timersOrdered_.raw().begin(), timersOrdered_.raw().end(), [&](const std::string& a, const std::string& b) {
        return timers_.at(a).start_ < timers_.at(b).start_;
      });
    
    std::string out2 = "Timer name | Timer value [s] | Share of registry total [%] | Start of timer [s]\n";
    FOR(i, timersOrdered_.size()) {
      const std::string& name = timersOrdered_(i);
      const Timer& timer = timers_.at(name);
      double timerVal = timer.getTimerVal_secDouble();
      double shareOfTotal = timerVal/totalTime;
      out2 += name+" | "+std::to_string(timerVal)+" | "+std::to_string(shareOfTotal*100)+" | "+std::to_string(std::chrono::duration<double>(timer.start_-totalStart_).count())+"\n";
    }

    return levelizeString(out + alignStringAt(out2, "|"), 1);
  }

 private:
  std::string registryName_;
  mutable std::mutex mutex_;
  //Array<Timer> timers_;
  std::chrono::high_resolution_clock::time_point totalStart_;
  std::unordered_map<std::string, Timer> timers_;
  Array<std::string> timersOrdered_;
};

class Timer { // TODOm: probably should all virtual destructor for memory stuff? so the destruction gets upcast? idk how it works honestly
 public:
  Timer() {}
  Timer(const std::string& name)
  : name_(name) {}
  double getTimerVal_secDouble() const {
    if(active_) warn("Timer \""+name_+"\" is still active!");
    return timerVal_secDouble_;
  }
 public:
  std::string name_;
  std::chrono::high_resolution_clock::time_point start_;
  double timerVal_secDouble_ = 0.0;
 protected:
  bool active_ = false;
};

class ScopedTimer : public Timer {
 public:
  ScopedTimer(const std::string& name)
  : Timer(name) {
    active_ = true;
    start_ = std::chrono::high_resolution_clock::now();
  }

  ~ScopedTimer() {
    active_ = false;
    timerVal_secDouble_ = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_).count();
    TimerRegistry::globalInstance().addTimer(*this);
  }
};

class StandardTimer : public Timer {
 public:
  StandardTimer(const std::string& name)
  : Timer(name) {
    active_ = false;
  }
  
  void start() {
    active_ = true;
    start_ = std::chrono::high_resolution_clock::now();
    lastStart_ = start_;
  }
  void stop() {
    active_ = false;
    timerVal_secDouble_ += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - lastStart_).count();
    TimerRegistry::globalInstance().addTimer(*this); // TODO: this can be organized and done better with hybrid pause maybe for static
  }
  void pause() {
    timerVal_secDouble_ += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - lastStart_).count();
  }
  void unpause() {
    lastStart_ = std::chrono::high_resolution_clock::now();
  }

 private:
  std::chrono::high_resolution_clock::time_point lastStart_;
};

#else

class TimerRegistry {
 public:
  TimerRegistry(const std::string& registryName) noexcept
  : registryName_(registryName) {};
 public:
  inline static TimerRegistry& globalInstance() {
    static TimerRegistry registry = TimerRegistry("Global Instance");
    return registry;
  }
  
  // for global tracking
  inline void start() {
    totalStart_ = std::chrono::high_resolution_clock::now();
  }

  inline void addTimer(const Timer&) noexcept {}
  
  inline std::string timingReportStr() const noexcept {
    std::string out = "==== Timing Report : Timers are off (TIMERS_ON == false) ====\n";
    out += "Registry name: "+registryName_+"\n";
    double totalTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-totalStart_).count();
    out += "Total registry time | " + std::to_string(totalTime) + "s\n";
    return levelizeString(out, 1);
  }
  
 private:
  std::string registryName_;
  std::chrono::high_resolution_clock::time_point totalStart_;
};

class Timer {
 public:
  Timer() noexcept {}
  Timer(const std::string&) noexcept {}
  ~Timer() noexcept = default;
};

class ScopedTimer {
 public:
  ScopedTimer(const std::string&) noexcept {}
  ~ScopedTimer() noexcept = default;
};

class StandardTimer {
 public:
  StandardTimer(const std::string&) noexcept {}
  ~StandardTimer() noexcept = default;
  
  void start() noexcept {}
  void stop() noexcept {}
  void pause() noexcept {}
  void unpause() noexcept {}
};

#endif

} // namespace MyFem
