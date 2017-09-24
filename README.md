# 04_Tank
Panzerspiel mit UE4

gdd:

.concept
driving around a landscape in a tank, scoring more tank kills than other players in a free-for-all or team-based battle. no simulation, just shooting stuff until it explodes.

.rules
win & lose: score limit.

tanks are destroyed after taking a certain amount of damage inflicted upon them by other players' tanks. 

tanks are supposed to move in a realistic fashion:
* they have turret rotation independent of the movement direction
* they accelerate and decelerate rapidly
* they should not be toppled by terrain or impacts
* they can climb certain angles

tanks fire shells:
* armor piercing sabot and/or other rounds
* impact angle, velocity, and location affect penetration and effectiveness of the shot

the game takes place in an arena setting:
* landscape containing hills, trees, bodies of water, buildings etc
* landscape is confined into a rectangular space by impassable terrain on the edges


.requirements
..3d
tank model(s)
landscape objects (houses, bridges, trees, ...)
water

..2d
tank textures
house textures
terrain materials
menu background(s)
buttons

..fx
particles (burning dead tanks, explosions on impact, treads throwing up dust, ...)


..audio
cannon firing
machine gun firing?
hits (glancing, penetrating, non-penetrating, ...)
engine
explosions (ground, tank, water, ...)
menu sounds
announcer (game start&end, kills, ...)
music pieces (menu, in-game, post-game, pre-game, ...)

..ai
path finding
positioning
aiming

..multiplayer
?
