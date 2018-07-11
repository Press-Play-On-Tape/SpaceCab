# SpaceCab
![Screenshot](/Assets/SpaceCabBanner.png)

## To do list:

- [SH 2018-07-07] ~~Add next level functionality.~~
- [SH 2018-07-05] ~~Change fuel functionality to only allow X units of fuel.~~
- [SH 2018-07-07] ~~Add the deployment of a ramp to actually let the customer get in the cab, would need to deploy it before landing. While the ramp is deployed without a customer in the cab, the thrusters should not be used at all. That way the player can't just have the ramp deployed at all times.~~
- [SH 2018-07-11]~~Make it so that after a certain amount of customers, the last one will ask you to go to the GATE (next level) and in the next level you still need to get that customer to a random destination. 
**I am going to close this one.  Customers tell you to go to the gate but then you start the new level fresh.  Too complex to add a message 'Go to Gate' followed by another message 'Go to 1' and the level introduction.**~~
- Check for space savings by removing sound.
- Check for space savings by compressing some images.



## Enhancements:

- [SH 2018-07-05] ~~Make the boot logo stay visible a little longer.~~
- [SH 2018-07-11] ~~Review the arrows – stay with lines or move to a single graphic.  My preference is the lines. **I am going to close this one.**~~
- [SC 2018-07-05] ~~Design a better ‘Goto ‘ graphic. And made it's position relative to the player~~
- [SC 2018-07-04] ~~Add detection when crashing into spikes.~~
- [SC 2018-07-08] ~~Add crash to bottom of screen when fuel runs out.~~
- Add crash when you hit an obstacle at high velocity.
- Make the physics more floaty for the left/right movement so that we really need to adjust our velocity to land.
- Crash cab if you land half on / half off a landing.
- Add an 'End of Game' sound or splash screen when you have completed the last level.
- Add a Space Cop that shows up sometimes. We need to avoid him while he's on the screen.
- Add switches mechanics to open/close parts of the level. In some cases to bring a customer you would need to open certain spots.
- If you fly off the top off the screen on the intro, you automatically end up at the next level. Note: waiting on decision regarding intro screen before fixing.
- [SC 2018-07-09] ~~Update the customer run animation to look more natural.~~
- [SH 2018-07-10] ~~Change logic to count number of fares (not dollars) before next level.~~
- [SH 2018-07-10] ~~Change go to gate logic so last fare says 'Go to gate' and gate opens.~~
- [SH 2018-07-10] ~~Prevent fuel going down while refuelling.~~
- [SH 2018-07-10] ~~Fare decreases as soon as customer calls for the cab.~~
- [SH 2018-07-10] ~~Update 'drop off' to ensure player is landed and within 8 - 16 pixels of sign.~~
- [SH 2018-07-11] ~~Added level offset to initLevels[] array so we can accurately place the level hadings.~~


## Bugs:

- [SH 2018-07-05] ~~Thrusters are still not showing up on the title screen~~
- [SH 2018-07-05] ~~On highscore screen when entering a name pressing down goes to letter j not Z.~~
- [SH 2018-07-07] ~~When going back to the Title screen, the number on the sign disappears.~~
- [SH 2018-07-10] ~~Fixed HUD issue on level 2.~~
- [SH 2018-07-10] ~~Prevent fuel going down while refuelling.  Not sure if this is actually fixed. 
   **[SC 2018-07-10] Not fixed yet!**
   [SH 2018-07-10] Fixed properly this time.~~
- The life counter sometimes starts at 0 and then goes to nine when we lose a life, and does it infinitely so can't be gameOver, no idea what causes that.
**This only occurs when you simply fly off the screen on the intro and do not carry a passenger.  Will fix with intro**
- Even when the customer says TO GATE, you can still deliver him to a numbered destination and have money. A fix for that could be to make the GATE a destination like the sign? and going thru the gate with the customer doesn't give money right now ( i think )
- Player spawn point for level 3 and 4 isn't right. Need to find an easier way to knwo which offset to use or maybe use the same way we position the customers? that would make it easier for me when i design and add new levels.
- [SH 2018-07-11] ~~Added level 5 but it's not loading after level 4 for some reason.  **Altered MAX_NUMBER_OF_LEVELS to 5 and moved this setting into the Levels.h so it is obvious.**


## Before going live:

- Confirm number of levels (MAX_NUMBER_OF_LEVELS)
- Confirm score to achieve in each level. 
  **[SC 2018-07-10] : it will be a number of customer requirement, some level will have only 1, for exemple in level 5 you only have to get 1 customer to the gate from the start, but the level is a hard one, so faster you can do it, the more money you get, but it's hard.**
