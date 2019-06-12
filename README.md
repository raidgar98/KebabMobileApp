# Kebab Mobile App

This is second part of whole project that provide simple interface and managment for small kebab restaurants. 

This part is mobile app for andoid devices (but if u want to test it, it's gonna run desktop). 

Things To Do with Highest Priority:

	- Add Missing comments

	- Rename varriables and methodes names
	
	- Add better storage managment

	- Add request to allow read and write into storage 
		(now user have to manually allow it in settings)

	- Create database automaticly if not detected


Things To Do with Standard Priority:

	- Add Translation (now Polish is the only language)

	- Add Encrytpion during transfer

	- Change storage directory (now it's user download folder)

	- Add dynamic extras

Things To Do with Lowest Priority:

	- Add settings for layout (color, darkmode, border options...)


I setup my Qt for android using this toutrial:
	
	https://www.youtube.com/watch?v=PU_po2mWwt8

When you setup your Qt now you can import all files to your new Project.

On your mobile device you have to create sqlite database in your download directory: dataBase
In this db, should be two tables, which you can create them with these querries:

	CREATE TABLE orders 
	(
        orderID int(11) PRIMARY KEY,
        dishName varchar,
        dishSouce int(3),
        extraMeat tinyint(1),
        extraSalad tinyint(1),
        extraFries tinyint(1),
        extraCheese tinyint(1),
        otherExtras tinyint(1),
        takeAway tinyint(1),
        isComplete tinyint(1),
        orderDateTime datetime
	);


	CREATE TABLE prices 
	(
	idPrice INTEGER PRIMARY KEY AUTOINCREMENT,
	name varchar,
	val decimal,
	fullName varchar,
	isExtra boolean
	);

If you want add permissions / icons / app name or stuff like this, go to project options and in
"Build Android APK" submenu click "Create Templates". Now in Project File Tree in "Other Files -> 
android -> AnroidManifest.xml" you can modify these options.

This is how it works (adding items and storaging it):

![Adding to DataBase](https://github.com/raidgar98/KebabMobileApp/blob/master/First.gif?raw=true)

And this is how syncing works:

![Syncing](https://github.com/raidgar98/KebabMobileApp/blob/master/Second.gif?raw=true)

And yes, it's so easy, just type address of serwer, where you want to send this files

If you have some troubles, bugs or recommendations write it to me:

	raidgar98@onet.pl

with title:

	[GitHub] KebabMobileApp

so my mail can filter it from SPAM to separate folder :)
