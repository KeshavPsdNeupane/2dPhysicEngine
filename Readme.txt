Hello Mr. Cherno



Technically, this is a simple 2D self-made physics engine that 
I modified a bit to make a Nokia Bounce Clone. It only has
 simulated friction and collision for two bodies, but that
 was enough for me to work with.

I’m a 3rd-semester CS student, just learning and picking up
 anything that excites my brain. This project wasn’t meant 
for job interviews or anything serious—I just wanted to 
prove to my friends and family that I could build a game
 from scratch. That’s why I didn’t bother with CMake or 
any build system.

How to Run
No fancy setup required. Just open the .sln file in 
Visual Studio, and it should work fine.
Static Linked SFML (32-bit). No need to install 
extra dependencies.


Map System
The maps are in Assets/Maps, and yeah, they might look a bit odd.
 But this was the best solution I could come up with.
 I had to write a custom XML parser using TinyXML
 to convert .xml files into .txt files that my game can read.

If you want to check out the parser,
here’s the GitHub link:
https://github.com/KeshavPsdNeupane/MapParserXML

Why Aren't All Objects the Same Type?
One major criticism I think I might get is
 why all objects aren’t a single base class.
 The reason is simple: each object has a 
different shape, and I had to manually adjust
 their collision boxes in the constructor.
 Trying to force everything into one class
 would’ve made things more complicated than necessary.


Final Words
And yeah, if this sounds a bit like an
 AI-generated README, sorry! English is
 my tertiary language, so I had to take
 some help to explain things properly.