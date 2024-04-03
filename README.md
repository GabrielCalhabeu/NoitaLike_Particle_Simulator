# NoitaLike_Particle_Simulator

Particle "simulator" inspired by the game Noita where different types of particles have different behavior.

The current implementation uses the SDL library for graphics and C++. Possible further work may include switching from SDL to OpenGL.

Press the following buttons to choose a different particle.

S - Sand: will fall and pile up

W - Water: will fall and try to fill the area it is in until it is level.

D - Dirt: will stay in the same place and act as a solid particle.

And left mouse button to place the particle down at the position of the pointer. Space will clean everything and restart from a blank.

Currently, some optimizations may be in order, such as quadtree search for active particles to compute, and parallel chunk computation.

<img src=noita_example.png style="width:480px;height:360px;">




