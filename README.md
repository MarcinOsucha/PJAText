# PJAText
Application used for working with files - geting number of lines, words, characters, geting numbers, anagrams and palindromes. Program gets input flags from conole or file, returns output to console or file.

## Flags:
<pre>
-f  | --file           | after this flag program excepts a path to file to check  
-n  | --newlines       | returns number of lines  
-d  | --digits         | returns number of digits  
-c  | --chars          | returns number of characters  
-dd | --numbers        | returns numbers  
-a  | --anagrams       | returns anagrams from file typed after this flag  
-p  | --palindromes    | returns palindromes from file typed after this flag  
-s  | --sorted         | returns sorted words in A-Z order  
-rs | --reverse-sorted | returns sorted words in A-Z order  
-o  | --output         | after this flag program excepts a path to output file  
-i  | --input          | after this flag program excepts a path to input file
</pre>
  
**Ways of typing parameters**
<pre>
a) -f path_to_file *flags
b) -i path_to_file_with_flags
</pre>

## Examples 
file.txt
<pre>
I have 4 cars. In my opinion it's better to have no opinion.
There is some food in the fridge.
</pre>

**Command**
<pre>
PJAText.exe -f file.txt -n -d
</pre>

**CMD Result**
<pre>
Number of lines: 2
Number of digits: 1
</pre>

**Command**
<pre>
PJAText.exe -i input.txt
</pre>

input.txt
<pre>
-f file.txt -c -dd -o output.txt -a pionion sono Three sdoa
</pre>

**CMD Result**
<pre>
Result saved to file.
</pre>

output.txt
<pre>
Number of characters: 94
Numbers: 4 
Anagrams: opinion There 
</pre>
