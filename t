## Execution Tests

| Status| Test						| Bash						|
|-------|---------------------------|---------------------------|												
| KO	|`./ls`						|no such file or dir		|	
| KO 	|`./`						|is a directory				|	
| KO	|`../`						|is a directory				|			

## CD

| Status| Test						| Bash								|
|-------|---------------------------|-----------------------------------|
| DK	|`unset HOME`, then `cd` 	|HOME not set						|

## ECHO

| Status| Test						| Bash				| 
|-------|---------------------------|-------------------|
				

## EXPORT

| Status| Test						| Bash								|
|-------|---------------------------|-----------------------------------|
| KO	|``			|`env | grep foo=` shows `foo=test`|
## UNSET

| Status| Test							| Bash							| 
|-------|-------------------------------|-------------------------------|

## ENV

| Status| Test										| Bash				| 
|-------|-------------------------------------------|-------------------|		

## EXIT

| Status| Test							| Bash											    |
|-------|-------------------------------|---------------------------------------------------|

## Pipe tests

| Status| Test										| Bash									| 
|-------|-------------------------------------------|---------------------------------------|
| KO	|`cat | cat | cat | ls`					|`ls` output then hangs, `enter` 3 times    |

## Variable Expansion Tests

Leading and trailling spaces in the output are denoted with the `█` character.

| Status| Test					| Bash				| 
|-------|-----------------------|-------------------|
| OK    |`echo $""`				|`(newline)`		|
| OK	|`echo $"USER"`			|`USER`				|
| OK	|`echo $'USER'`			|`USER`				|
| OK	| `echo $"fake"`		|	`fake`		    |		

## Quote Handling Tests

Leading and trailling spaces in the output are denoted with the `█` character.

| Status| Test					| Bash				| 
|-------|-----------------------|-------------------|
| OK	|`echo  $''USER`		|`USER`				|	


## Heredoc Tests
| Status| Test								| Bash							| 
|-------|-----------------------------------|-------------------------------|
| 	|`<< END cat`; `$USER$USER`; `END`	|`usernameusername`				|		
| 	|`<< END cat`; `$USER'$USER'`; `END`|`username'username'`			|		
| 	|`<< END cat`; `$USER"$USER"`; `END`|`username"username"`			|		
|  	|`<< END cat`; `$USER $USER`; `END`	|`username username`			|			
| 	|`<< END cat`; `helloEND`			|Heredoc keeps waiting for input|
| 	|`<< END cat`; `ENDhello`			|Heredoc keeps waiting for input|
| 	|`<< END cat`; `helloENDhello`		|Heredoc keeps waiting for input|						
| 	|`< Makefile cat | << END cat`		|Heredoc + cat execute			|		
| 	|`export $VAR=test`					|`env` shows `VAR=test`			|			
| 	|`<< $VAR cat`; `$USER`; `$VAR`		|Heredoc ends with `$VAR` input	|	

## Redirection Tests

| Status| Test					| Bash													|
|-------|-----------------------|-------------------------------------------------------|			  									
| OK(parse)	|`< Ma < Makefile cat`	|Ma: no such file or directory (no cat output)			|								
| OK(parse)	|`<a cat <b <c`			|`cat` shows contents of file `c` only					|
| OK(parse)	|`<a cat <b <c`			|`b: Permission denied`, does not show `c`				|
| OK(parse)	|`>a cat <b >>c`		|Create empty `a`, `c` gets contents of `b` (because `cat<b` will output content of b)				|		
| OK(parse)	|`>a ls >b >>c >d`		|`a`, `b`, `c`, `d` created, `ls` ouput only in `d`		|
| OK(parse)	|`>a ls <e >>b >c`		|`e`: no such file; `a` created `b` and `c` not created	|
| OK(parse)	|`cat -e >t1 <t2`		|`t2`: no such file; `t1` created						|
| OK(parse)	|`echo 2 >o1 >>o2`		|`2` written to `o2`, `o1` empty						|
| OK(parse)	|`echo 42 >o2 >>o1`		|`o1` contains `42`, `o2` empty							|
| OK(parse)	|`echo hello > k\ 1`	|Creates file "`k 1`"									|
| OK(parse)	|`echo test >f test1`	|Creates file `f` with contents `test test1`			|	
| OK(parse)	|`fakecmd hello > z`	|Command not found, file `z` created					|
| OK(parse)	| `ls > a > b -l`		| create empty `a` and `b` with content of `ls -l`		|		
| OK(parse)	|`ls > p | env > q`	|`p` contains `ls` output; `q` contains `env` output	|				
| OK(parse)	|`echo "File A" > a`	|Create file `a` with contents `File A`					|				
| OK(parse)	|`echo "File B" >> b`	|Create file `b` with contents `File B`					|			
| OK(parse)	|`echo File C >c`		|Create file `c` with contents `File C`					|				
| OK(parse)	|`chmod 000 b`			|Remove rights to `b` file								|					
| OK(parse)	|`chmod 644 b`; `rm a`	|Restore rights to `b` file, delete `a`					|			
| OK(parse)	|`rm a b c`				|Delete `a`, `b` and `c` files							|				
| OK(parse)	|`< Ma < Maa echo a`	| bash: Ma: No such file or directory + `echo a` don't get executed|	
| OK(parse)	|`echo a < Ma < Maa`	| bash: Ma: No such file or directory + `echo a` don't get executed|	
| OK(parse)	| `echo hello < txt sweetie` (txt exist)	| `hello sweetie` |					
|			| `ls > e | cat<e`  | bash: e: No such file or directory + `e` created with content of ls |		
|			| `cat<f | ls >f`			|	bash: f: No such file or directory + `f` get created with ls content |	
|			| `echo hello > a | echo fuck > a` | behavior change; sometimes a contains `hello` sometimes `fuck` |	
|			| `echo hello > a > b | echo fuck >b` | `a` and `b` created b contains hello, b doesn't get overwritten |	
|			| ` echo hello > b| echo ddd>> b` | `b` created b contains hello, b doesn't get overwritten |		

## Signal Tests
| Status| Test						| Bash								| 
|-------|---------------------------|-----------------------------------|												
| 	|`abc` + `ctrl+\`			|does nothing						|							
| 	|`cat` + `enter` + `ctrl+\`	|quit cat; do not kill shell		|		

## Other Syntax Error Tests
| Status| Test						| Bash						| 
|-------|---------------------------|---------------------------|				
| OK	|`echo test > "$t"`			|write to file `"abc def"`	|		


## Other Exit Status Tests
| Status| Test					| Bash						|
|-------|-----------------------|---------------------------|
| 	|`fake_cmd`				|Command not found			|
| 	|`ls not_a_path`		|No such file or dir		|
| 	|`./not_executable_file`|Permission denied			|
| 	|`cat clac 3`			|2 error msg				|
| 	|`cd $?`				|Number: no such file or dir|
| 	|`cat |||`			|syntax error				|
| 	|`echo "hell`			|unexpected EOF + syntax	|
