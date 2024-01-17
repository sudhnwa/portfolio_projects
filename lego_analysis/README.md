This project aims to provide answers to the following questions

What percentage of all licensed sets ever released were Stars Wars themed?

In which year was Star Wars not the most popular liecensed theme(in terms of number of sets released that year). 


Meta data :

lego_sets.csv

set_num: A code that is unique to each set in the dataset. This column is critical, and a missing value indicates the set is a duplicate or invalid!

set_name: A name for every set in the dataset (note that this can be the same for different sets).

year: The date the set was released.

num_parts: The number of parts contained in the set. This column is not central to our analyses, so missing values are acceptable.

theme_name: The name of the sub-theme of the set.

parent_theme: The name of the parent theme the set belongs to. Matches the `name` column of the `parent_themes` csv file.

parent_themes.csv

id: A code that is unique to every theme.

name: The name of the parent theme.

is_licensed: A Boolean column specifying whether the theme is a licensed theme.
