# MsGui
Lightweight C++ GUI library for embedded systems. 

Repository is currently under development. 
My main goal is to provide tiny GUI library for very low resources embedded devices which uses very strict resources.

Milestones:
- implementation of GUI for monochrome displays
- implementation of GUI with signal layer
- implementation of GUI for color displays

Problems:
- how to fit in memory when frame buffer is to big for RAM memory?
  Allowing to rendering with buffering and without buffering (slower performance, better memory efficiency)
  Rendering without buffering, calculate pixel in runtime with requesting calculation form widgets just in time.
  
