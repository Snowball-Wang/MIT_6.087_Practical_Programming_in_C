# Problem Set 7

**Using and creating libraries. B-trees and priority queues. **

## Problem 7.1

In this problem, we will be utilizing the SQLite serverless database library to load and query a database file. The required library `libsqlite3.so`and header file `sqlite3.h`appear to be installed on some Athena workstations (but not on the Athena server). If you cannot find it on your own machine's distribution, you can download the source code from **http://sqlite.org/download.html**. Generally, for your machine, you will have to compile the library yourself. For Linux, use the `.tar.gz`source code amalgamation package that contains the configure and makefile support. To compile for Linux, extract the files, run `./configure`, `make`, and `nake install`. For other platforms, you will need to compile and install the library yourself.

* Download the source code `prob1.c` and movie database file `movie.db` from Stellar. The database contains a list of movies indexed by BarCode. The list also contains the MovieTitle, MovieCategory, ProductionYear, Format, Language, and Web fields for each movie. In this part, we will use the `sqlite3` library to load this database and perform simple SQL queries. (In case you're curious, the database lists information for movies available from library in the Sidney Pacific dormitory.) The source code will get you started.

  For this part, you need to fill in the missing code to open the database file, perform an SQL query, and close the database. In particular, you will be expected to use the `sqlite3_open()`, `sqlite3_exec()`, and `sqlite3_close()` functions in your code. Read the documentation available on the SQLite website for details.

  Via Stellar, turn in your code for this part, as well as your program's output for the first free SQL queries provided in your code.

  **Answer:**

  ```c
  /* load the database */
  sqlite3 *db = NULL;
  char *errmsg = NULL;
  int ret = sqlite3_open(argv[1], &db);
  if (ret != SQLITE_OK)
  {
      fprintf(stderr, "Cannot open database : %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return 1;
  }
  printf("Open database successfully!\n");
  
  /* execute the SQL query */
  ret = sqlite3_exec(db, sql, display_result, NULL, &errmsg);
  if (ret != SQLITE_OK)
      fprintf(stderr, "Fail to execute the SQL query: %s\n", errmsg);
  
  /* close the database when you're done with it */
  sqlite3_close(db);
  printf("Close database!\n");
  return 0;
  ```

  **Output:**

  ```
  // For sql query: SELECT * FROM movies WHERE ProductionYear < 1950
  BarCode: [3141973] MovieTitle: [Casablanca] MovieCategory: [Drama] ProductionYear: [1943] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0034583] 
  BarCode: [3142179] MovieTitle: [Charlie Chaplin Centennial Collection: Modern Times] MovieCategory: [Comedy] ProductionYear: [1936] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0027977] 
  BarCode: [3142180] MovieTitle: [Charlie Chaplin Centennial Collection: Gold Rush/ Pay Day] MovieCategory: [Comedy] ProductionYear: [1936] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0015864] 
  BarCode: [3142225] MovieTitle: [Citizen Kane] MovieCategory: [Drama] ProductionYear: [1941] Format: [DVD] Language: [English] Web: [http://us.imdb.com/Title?0033467] 
  BarCode: [3142926] MovieTitle: [El Tercer Hombre (The Third Man)] MovieCategory: [Thriller] ProductionYear: [1949] Format: [DVD] Language: [Spanish] Web: [http://www.imdb.com/title/tt0041959/] 
  BarCode: [3143092] MovieTitle: [Mr. Smith Goes to Washington] MovieCategory: [Drama] ProductionYear: [1939] Format: [DVD] Language: [English] Web: [http://www.imdb.com/title/tt0031679/] 
  BarCode: [3143217] MovieTitle: [Gone with the Wind] MovieCategory: [Drama] ProductionYear: [1939] Format: [DVD] Language: [English] Web: [http://www.imdb.com/title/tt0031381/] 
  BarCode: [3143294] MovieTitle: [Twelve O'Clock High] MovieCategory: [Action] ProductionYear: [1949] Format: [DVD] Language: [English] Web: [http://www.imdb.com/title/tt0041996/] 
  BarCode: [3143301] MovieTitle: [Wizard of Oz, The] MovieCategory: [Family] ProductionYear: [1939] Format: [DVD] Language: [English] Web: [http://www.imdb.com/title/tt0032138/] 
  BarCode: [3144262] MovieTitle: [Public Enemy, The] MovieCategory: [Action] ProductionYear: [1931] Format: [DVD] Language: [English] Web: [http://www.imdb.com/title/tt0022286/] 
  BarCode: [3144263] MovieTitle: [Little Caesar] MovieCategory: [Action] ProductionYear: [1931] Format: [DVD] Language: [English] Web: [http://www.imdb.com/title/tt0021079/] 
  BarCode: [3144275] MovieTitle: [Scarface (1932)] MovieCategory: [Action] ProductionYear: [1932] Format: [DVD] Language: [English] Web: [http://www.imdb.com/title/tt0023427/] 
  
  // For sql query: SELECT * FROM movies WHERE Format == \"VHS\"
  BarCode: [3141961] MovieTitle: [Star Wars: Episode VI - Return of the Jedi] MovieCategory: [Action] ProductionYear: [1978] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0086190] 
  BarCode: [3141962] MovieTitle: [Star Wars: Episode V - The Empire Strikes Back] MovieCategory: [Action] ProductionYear: [1978] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0080684] 
  BarCode: [3141963] MovieTitle: [Star Wars: Episode IV - A New Hope] MovieCategory: [Action] ProductionYear: [1978] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0076759] 
  BarCode: [3141971] MovieTitle: [La Dolce Vita] MovieCategory: [Drama] ProductionYear: [1961] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0053779] 
  BarCode: [3141972] MovieTitle: [It's A Wonderful Life] MovieCategory: [Family] ProductionYear: [1955] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0038650] 
  BarCode: [3141973] MovieTitle: [Casablanca] MovieCategory: [Drama] ProductionYear: [1943] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0034583] 
  BarCode: [3141974] MovieTitle: [Victor Victoria] MovieCategory: [Comedy] ProductionYear: [1982] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0084865] 
  BarCode: [3141975] MovieTitle: [Some Like It Hot] MovieCategory: [Comedy] ProductionYear: [1959] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0053291] 
  BarCode: [3142179] MovieTitle: [Charlie Chaplin Centennial Collection: Modern Times] MovieCategory: [Comedy] ProductionYear: [1936] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0027977] 
  BarCode: [3142180] MovieTitle: [Charlie Chaplin Centennial Collection: Gold Rush/ Pay Day] MovieCategory: [Comedy] ProductionYear: [1936] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0015864] 
  BarCode: [3142181] MovieTitle: [Zorba the Greek] MovieCategory: [Drama] ProductionYear: [1964] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0057831] 
  BarCode: [3142190] MovieTitle: [Ridicule] MovieCategory: [Drama] ProductionYear: [1996] Format: [VHS] Language: [French] Web: [http://us.imdb.com/Title?0117477] 
  BarCode: [3142204] MovieTitle: [Delicatessen] MovieCategory: [Others] ProductionYear: [1991] Format: [VHS] Language: [French] Web: [http://us.imdb.com/Title?0101700] 
  BarCode: [3142206] MovieTitle: [Lawrence of Arabia] MovieCategory: [Drama] ProductionYear: [1962] Format: [VHS] Language: [English] Web: [http://us.imdb.com/Title?0056172] 
  BarCode: [3142211] MovieTitle: [Art of Survival, The] MovieCategory: [Documentary] ProductionYear: [1995] Format: [VHS] Language: [English] Web: [] 
  BarCode: [3142672] MovieTitle: [Fiorile] MovieCategory: [Drama] ProductionYear: [1993] Format: [VHS] Language: [Italian] Web: [http://www.imdb.com/title/tt0106911/] 
  BarCode: [3142673] MovieTitle: [Padre Padrone] MovieCategory: [Drama] ProductionYear: [1977] Format: [VHS] Language: [Italian] Web: [http://www.imdb.com/title/tt0076517/] 
  BarCode: [3142674] MovieTitle: [Night of the Shooting Stars, The] MovieCategory: [Drama] ProductionYear: [1982] Format: [VHS] Language: [Italian] Web: [http://www.imdb.com/title/tt0084422/] 
  BarCode: [3142675] MovieTitle: [St. Michael Had a Rooster] MovieCategory: [Drama] ProductionYear: [1972] Format: [VHS] Language: [Italian] Web: [http://www.imdb.com/title/tt0069215/] 
  
  // For sql query: SELECT * FROM movies WHERE Language == \"Spanish\"
  BarCode: [3141936] MovieTitle: [Amores Perros] MovieCategory: [Drama] ProductionYear: [2001] Format: [DVD] Language: [Spanish] Web: [http://us.imdb.com/Title?0245712] 
  BarCode: [3142205] MovieTitle: [Buena Vista Social Club] MovieCategory: [Drama] ProductionYear: [1999] Format: [DVD] Language: [Spanish] Web: [http://us.imdb.com/Title?0186508] 
  BarCode: [3142207] MovieTitle: [Women on the Verge of a Nervous Breakdown] MovieCategory: [Comedy] ProductionYear: [1988] Format: [DVD] Language: [Spanish] Web: [http://us.imdb.com/Title?0095675] 
  BarCode: [3142655] MovieTitle: [Talk to Her] MovieCategory: [Drama] ProductionYear: [2002] Format: [DVD] Language: [Spanish] Web: [http://www.imdb.com/title/tt0287467/] 
  BarCode: [3142855] MovieTitle: [Motorcycle Diaries, The] MovieCategory: [Drama] ProductionYear: [2004] Format: [DVD] Language: [Spanish] Web: [http://www.imdb.com/title/tt0318462/] 
  BarCode: [3142862] MovieTitle: [Maria Full of Grace] MovieCategory: [Drama] ProductionYear: [2004] Format: [DVD] Language: [Spanish] Web: [http://www.imdb.com/title/tt0390221/] 
  BarCode: [3142926] MovieTitle: [El Tercer Hombre (The Third Man)] MovieCategory: [Thriller] ProductionYear: [1949] Format: [DVD] Language: [Spanish] Web: [http://www.imdb.com/title/tt0041959/] 
  BarCode: [3144037] MovieTitle: [Pan's Labyrinth] MovieCategory: [Drama] ProductionYear: [2006] Format: [DVD] Language: [Spanish] Web: [http://www.imdb.com/title/tt0457430/] 
  ```

* In this part, you will read the entire table into a B-tree, sorted by the name of the movie(assumed to be unique). In the provided code, you will find mostly completed for the B-tree. Complete the missing lines in the B-tree functions. For this and future parts, use the final SQL query, which reads the entire movies table.

  Once you have done this, add code to your `main` function to print the results of an inorder traversal of the B-tree to a file (second command line argument to the program). Via Stellar, submit online your code and the file containing the result of the traversal.

  **Answer:** See `prob1b.c` and `prob1b.txt`.
  
* Now, modify your code to ask the user for a movie title. Use the `find_value()` function to locate the movie and print the movie information using `display_record()` to the console. Your program should continue continue to ask the user until the input string is an empty line. Be sure to remove the trailing newline `\n` character from the end of the string returned from `fgets()`.

  Submit via Stellar your code for this part and your console output for a few illuminating test cases. For instance, `Citizen Kane`, `Casablanca` and `Gone with the Wind` are all in the database.

  **Answer:** See `prob1c.c` and `prob1c.txt`

  ```
  Please input the movie name: Citizen Kane
  [#126] Citizen Kane (1941): Drama, DVD, English, <http://us.imdb.com/Title?0033467>
  Please input the movie name: Casablanca
  [#62] Casablanca (1943): Drama, VHS, English, <http://us.imdb.com/Title?0034583>
  Please input the movie name: Gone with the Wind
  [#722] Gone with the Wind (1939): Drama, DVD, English, <http://www.imdb.com/title/tt0031381/>
  Please input the movie name: Forest Gump
  Forest Gump not found
  Please input the movie name: Forrest Gump
  [#290] Forrest Gump (1994): Drama, DVD, English, <http://www.imdb.com/title/tt0109830/>
  Please input the movie name: Fight Club
  [#14] Fight Club (2000): Drama, DVD, English, <http://us.imdb.com/Title?0137523>
  Please input the movie name: 
  Input is an empty string, exiting...
  ```

* For this final part, you will create your own library from the code you wrote for your program. In particular, you should provide the following functions:

  * `int initialize_db(const char * filename)`; - loads the SQLite database from file `filename` and reads the contents into a B-tree, sorted by movie title. The function should return zero if successful, or non-zero otherwise. Don't forget to close the database when you're done loading from it.
  * `int locate_movie(const char * title)`; - searches the B-tree for the movie with title `title` and writes the result to the console. The function should return non-zero if a record was found, or zero if no record matches the specified title.
  * `void dump_sorted_list(const char * filename)`; - performs an inorder traversal of the B-tree, dumping the sorted list of movies to the file specified by `filename`. The function does not return anything.
  * `void cleanup(void)`; - this function should free the memory used by the B-tree and its records. This function does not return anything.

  Be sure to remove your main function from the library, and go ahead and compile this library. On Stellar, you will find the program `prob1d.c` that will use the library. Compile the program, either statically or dynamically linking it against your library (and `sqlite3`).

  Submit via Stellar a copy of your code and the output of running the program defined in `prob1d.c`.
  
  **Answer:** See `mylib.c`, `prob1d_static.txt` and `prob1d_dynamic.txt`.
  
  Output for executing `locate_movie` in `prob1d.c`:
  
  ```
  [#126] Citizen Kane (1941): Drama, DVD, English, <http://us.imdb.com/Title?0033467>
  Movie "Ponderosa" not found!
  [#42] Gosford Park (2001): Drama, DVD, English, <http://us.imdb.com/Title?0280707>
  [#1185] Transformers (2007): Action, DVD, English, <http://www.imdb.com/title/tt0418279/>
  [#722] Gone with the Wind (1939): Drama, DVD, English, <http://www.imdb.com/title/tt0031381/>
  [#178] When Harry Met Sally (1989): Comedy, DVD, English, <http://us.imdb.com/Title?0098635>
  Movie "Avatar" not found!
  Movie "Simpsons Movie, The" not found!
  [#380] American Pie 2 (2001): Comedy, DVD, English, <http://www.imdb.com/title/tt0252866/>
  [#796] Superman Returns (2006): Action, DVD, English, <http://www.imdb.com/title/tt0348150/>
  ```
  
  **Attention**: Before executing `prob1d_dynamic`, you need to add the library path to the shell environment by `export LD_LIBRARY_PATH=your_library_path`. 