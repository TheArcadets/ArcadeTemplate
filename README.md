# **Arcade Template**
# Videos

## [Introduction To The Template](https://youtu.be/2zFPTH0Le6I)

## [Blueprint Game](https://youtu.be/e2l1Qs2iVNM)

## [C++ Game](https://youtu.be/2lm2lMLiCOc)

## [Arcade Framework Overview](https://youtu.be/u5GDvrWCm8M?si=GIKYKrgyEYpeq9dn)

[Texture Maps Video](https://youtu.be/7g3O1TmQGac).
# Creating a Blueprint only game
To create a blueprint only game you need to first create a content only plugin by going into Edit->Plugins->Add and choosind the Content Only Plugin. Name this plugin to be the full name or the abbreviated name of your game. Once created you need to place **ALL** of your game's content within this plugin's content folder. Once the game is finished you should be able to send use the entirety of this plugin as your full game and it will allow us to easily add your game to the Arcade.
Steps:
1. Create a Content Only Plugin with the name of your game
2. Create your game and ensure all needed content for your game is held within your game plugin
3. Upon completion of your game submit your game's plugin to us.
# Creating A C++ Game
To create a game that supports and can use C++ you need to first add *any* C++ class to the base template. This can be done by going into Tools->New C++ Class. **You will NOT and CANNOT use this added class within your game. This is only to generate the required build files to use C++.** I recommend choosing None as the class option and then naming it something like "DONOTUSE" to make this very clear. Once it finished adding everything in, you can move on. The next step is to go into Edit->Plugins->Add and add in the top option of Blank for your plugin. Name the plugin the title of your game. Once this finishes compiling you should then have a plugin content folder for your game. ALL of your game's content needs to be within this content folder. You can add in C++ classes to your game plugin by using Tools->New C++ Class and changing the module option (Drop down to the right of your class name) to be the runtime module of your game's plugin. **Failing to do this will mean your C++ class will not appear within your game's plugin folder.**
Steps:
1. Add in any type of C++ class to the template project to generate support for C++ coding.
2. Add in a new "Blank" plugin named the title of your game.
3. Ensure all your game's content is held within the plugin content folder
4. Ensure any C++ classes are using your game plugin's module
5. Upon completion of your game submit your entire game plugin to us.
# Arcade Framework
## What is it?
The Arcade Framework is a plugin that is included with the template. This plugin is what will allow your game to be added into the Arcade. It is very important that you do not directly alter any of the content within this plugin. You can and should create child classes of certain classes and/or duplicate some of the provided blueprints. However, you should not directly alter any of the content or it could lead to complications when adding your game into the Arcade.
## Project Settings
With a few exceptions, you should not alter any project settings within your game. If you need to alter any project settings, please check and verify with an admin first to ensure it won't cause conflicts with adding additional games to the Arcade. An allowed exception is changing the default editor map so your editor loads directly into one of your levels instead of the engine provided template level.
You will also notice that the default GameMode is set to BP_BaseGameModeDONOTALTER and the Game Instance is set as ArcadeInstance. You cannot alter or change these settings, so for your game you will not be able to use the default Unreal Engine GameMode or a custom Game Instance. You will also not be able to use GameState or PlayerState.
## Framework Classes
### CabinetData
The CabinetData class is a data asset class that your game will have to have in order to be seamlessly added into the Arcade. There is an example one called DA_YourGameData found within the Framework's Content/Data folder. You can either duplicate this asset for your game and rename it to the title of your game, or you can create a new Data Asset of type Cabinet Data.
Inside the Data Asset is four categories:
- Team Info
- Game Info
- Cabinet Customization
- Launch Info
**Team Info:** contains a text array where you can place the names and roles of everyone who worked on the game. Team name can be used if your team has an overall name they would like associated with the game.
**Game Info:** contains a spot to place the title of your game, a description of your game, and to choose the genre of your game. If you choose “other” as your genre then a new text box will appear to type in your game’s genre. There is also the Max Players variable. This is currently locked to have a value of 1 as this first iteration won’t be supporting multiplayer games, but as we add in that functionality in the future you will be able to choose the max number of players that can play your game online together.
**Cabinet Customization:** contains what your Arcade cabinet will look like within the Arcade Hub. Currently the cabinet types available are being worked on but once they are available we’ll let everyone know. So for now this can remain as none. If your team wants to create your own arcade cabinet design then let us know and we can try to work together to ensure it fits the requirements we are following with creating the cabinet style. Game icon will be the icon of your game that is displayed on the arcade screen before playing the game. Cabinet front and sides are locations for textures where an artist can create custom art to customize the look of your arcade cabinet. Once cabinet styles are finalized we will provide the UV outlines you’ll need to create these textures.
**Launch Info:** is where you will choose the initial map for your game. This can dive the player straight into the game or it can lead to a main menu for your game. The choice is entirely up to you, but once again make sure the map you have selected is within your game’s plugin folder. Use start tag is used if your game uses any tagging on the player start’s located within your game. Game mode class is where you will place the default arcade game mode for your game. But only add this if your game uses just the one game mode within every level. Otherwise you should leave this blank and ensure you are manually placing in your arcade game modes into each level as needed.
### ArcadeSoundTriggerVolume
This class is was designed to give you an optional tool to help streamline the development process. The trigger volume can be used to designate locations where randomized ambient sounds, music, or effects caan be played. If you choose to use this, you should duplicate the blueprint of it found within the Framework Content/Audio folder. The class has options to designate whether the played sounds should loop continuously while overlapped. The Sounds array holds any of the sounds you want as options to play. Each time a loop repeats or is triggered to play with an overlap the class will play a random sound from this array. By using the PitchShiftMin and PitchShiftMax values you can set a random pitch variance to reduce repetitive sounds. The MaxIndividualRepeats variable sets the maximum number of times an individual sound can repeat before switching to another random sound from the array. Although this only has an effect if the volume is set to loop.
### ArcadeController
If you want to add in your own custom player controller, then it needs to be a child of this class. The class behaves in a very similar way to the standard player controller. However you do not need to add Input Mapping Contexts the typical way. You instead add one or multiple mapping contexts into the GameMapping array. The ArcadeController is setup to automatically add these mappings to the player controller. From there you can setup inputs in the standard way through blueprints or C++. **You cannot use the escape key with any input action.** This key is being reserved to open a global Arcade pause menu.
### ArcadeFunctions
This is a BlueprintFunctionLibrary class that contains four functions for you to use.
- Arcade Open Level
- Arcade Stream Level
- Arcade Unload Stream Level
- Quit to Hub
You can quickly find these functions within a blueprint graph by typing in Arcade and it should show up in the "Arcade Functions" category.
**You should not use the standard Unreal Engine Open Level or Level Streaming functions within your game.** Doing so will make your game unable to be added into the Arcade.
**Arcade Open Level:** This function should replace any usage of the standard Open Level function in your game. This class takes a Soft Object Pointer to a level within your project. This means that in blueprints you can use a drop down selection to choose which level is being opened instead of having to manually type out a name. In C++ you just need to pass in pointer to the level you want to open as well as a world context object in the form of "this" Example:
```ArcadeFunctions::ArcadeOpenLevel(this, LevelToOpenPointer);```
**Arcade Stream Level:** This function should replace any usage of level streaming or loading level instances in your game. The context and usage works the same as the Arcade Open Level function, but it also returns a pointer to the level being streamed in. This pointer can then be saved as a variable to be referenced later and used to unload the level as needed. C++ Example:
```ArcadeFunctions::ArcadeStreamLevel(this, LevelToStreamPointer);```
**Arcade Unload Stream Level:** This function takes in a pointer to a streamed level and will unload it when called. C++ Example:
```ArcadeFunctions::ArcadeUnloadStreamLevel(this, LevelToUnload);```
**Quit To Hub:** This function will do nothing in the context of your game, but within the Arcade it will make the game close out and return the player to the Arcade. You do not have to use this function as the global Arcade pause menu will have the same function available to quit playing a game in the Arcade. However, if you would like to indicate any triggers that make the player quit playing the game. You can use this function. C++ Example:
```ArcadeFunctions::QuitToHub();```
### Arcade Game Mode
This “game mode” is actually just a base actor class within Unreal engine that is designed to act in a similar manner to Unreal’s game mode. In fact if you look at the inheritance hierarchy, the base Unreal game mode is in itself an actor that is automatically spawned in by each level when the game starts to act as a game manager. The arcade game mode does this for you except you will need to manually place one in your game. Using the Arcade Game Mode you should see the options to assign a player pawn, player controller, and also to use a spawn tag. If you check the use spawn tag it will give the option to type out the tag that matches to a given player start. Player Pawn is the player character itself that you will play as. If Player controller is left blank then it will use the default ArcadeController class for the player controller. Otherwise, you can chooose an ArcadeController child class instead. Beyond that if you open up the full blueprint graph or create a c++ child class, you can use it for everything you would use a regular gamemode for.
The Arcade Game Mode also features another function for you to use that can be found in the Arcade Functions category within the blueprint of your ArcadeGameMode.
**Get Arcade Game Instance:** This function returns the ArcadeInstance that is the assigned game instance of your game. You can also get access to the game instance through the standard Get Game Instance and casting to ArcadeInstance workflow, but this function streamlines that process slightly within the Arcade Game Mode.
### ArcadeInstance
The ArcadeInstance class is deigned to support saving structs of any kind into a key value pair map. This can allow you to use the Game instance to save variables in the form of a struct if your game requires that. The ArcadeInstance itself has three Arcade Functions for you to use for that:
- Save To Instance
- Load From Instance
- Clear Struct
**Save To Instance:** this function takes in a "key" in the form of a string and a "Value" that can be any struct you make. Allowing the instance to dynamically hold any game data you might need it for.
**Load From Instance:** This function takes in a "key" value in the form of a string and will return success or failure as well as the custom struct matching the key. To actually use this struct in blueprints you will need to assume it is of the correct struct type and use a "Break 'YourStruct'" node to access the values on a success.
**Clear Struct:** This function removes all the saved structs from the Game's Instance. You do not have to use this as any instance data will be cleared upon exiting your game and returning to the Arcade. But you have the option available if you need it.
### M_MasterMat
Last thing for the template is optional for you to use but I decided to include it to try to help out the arcade with shader compilation and memory usage. That is this custom Master Material, called M_MasterMat. If you do use this to create material instances then you cannot make any changes to the base MasterMaterial. Instead only use it to create material instances.
There are a lot of options within this material that should work for the majority of your models, but there still might be some you’ll need to create your own material for. If you want more information on how to use this just let me know. But it supports texture maps for Albedo, AO, Emissive, Metallic, Roughness, Specular, Normal maps, Dirt, Surface Imperfections, and Packedtexture maps that contain Metallic, Roughness, and Ambient Occlusion. The default setup assumes Metallic in the Red Channel, Roughness in the green, and AO in the blue channel. However, it does also give you the option to change which channel is used for which so that the packing order of your map can change. If you are unfamiliar with using Packed texture maps I do have a video that covers texture maps in detail including packed texture maps that I will link on here as well in the Videos section. Although that is more general information.
# Recap
You need to use the Arcade game mode, you need to have a cabinet data asset filled out for your game, you need to use the Arcade level loading functions instead of the normal Unreal Engine ones, If you want to use a custom player controller then it needs to be a child of the Arcade Controller, if you need to save any variables to the game instance, then you should use the custom Functions of the instance which can easily be gotten through the Arcade Game mode or you can also manually get the game instance and cast it to the ArcadeInstance to use those functions as well. The sound trigger volume is there for you to use if you would like but you don’t have to. The same applies for the provided master material, but if you do use it, it should help the overall performance of your game within the hub to be better. Lastly and most importantly, ALL of your game’s content, including any child classes of the framework, or material instances from the master material. NEED to be housed within your game’s plugin folder.
If you need any additional assistance please reach out to me and I’ll be happy to help.
