# INI-Number-Generator
Progress:

- [04/05/2022] After writing some code I made it public, slowly you will see updates.

- [05/05/2022] I continued a bit of code, fixed some bugs and started adding the commons. (Link that I will need: https://www.studioaleo.it/struttura-codice-fiscale.html)

- [12/05/2022] I had fixed the list of towns, and create a new bug, that i will fix.

- [06/03/2025] I removed the list of towns and inserted a database.

- [11/03/2025] Changed the date of birth entry and created the algorithm to generate the code

How to run: 

- Download the project
- Open it via Visual Studio 2022.
- Install the following packages via vcpkg: jsoncpp, libpq. Use the official guides to get these packages into Visual Studio 2022.
- From the project settings put c++ in the C++ Standard 17 ISO version (/std:t++17).
- Configure a postgresql database and import this database: https://www.gardainformatica.it/database-comuni-italiani
- Change the settings of the configuration json file to your own database containing city data.
- And run the code!
