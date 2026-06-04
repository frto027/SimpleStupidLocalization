# CSV Guide

The mod is designed to be compat with polyglot's csv format, but not as strict as polyglot's requirement.

- All rows before `Polyglot,` are paresed but be ignored. You can add comments before that. The `Polyglot,` line is required, just like what polyglot requires.
- first column is key, seconed column is description, third column is value, others are optional different languages.
- We don't require the colmn count, you need at least 3 column. But make sure every line have same column count, so `ssl10n.csv` can synchronize it to crowdin. This mod doesn't require it. **You can just save your csv file with MSExcel.**
- When a key is loaded twice, the empty value will be ignored and be merged with old value if avaliable. **Space is not empty value**.
- Description is ignored. However translators can see the description, so add one if possible.
- works with CRLF(`\r\n`), or LF(`\n`)
- Use UTF-8 encoding. The mod doesn't touch your texts' encoding. The file encoding depends on your usage. For Unity, they use UTF-8.
- Everything in text is kept, including space.


# Work with Microsoft Excel

In some windows system, excel doesn't use UTF8 encoding by default. 

Always save the file with `UTF-8 with BOM` to prevent encoding problem with microsoft's product. Both `ssl10n.csv` and `sslocalization` has BOM support.

# Example

These csv file can be parsed by the mod. Be aware that they're not compatable with polyglot.

You can always use the [Polyglot's sheet](https://docs.google.com/spreadsheets/d/17f0dQawb-s_Fd7DHgmVvJoEGDMH_yoSd8EYigrb0zmM/) if you want.

simple example
```
Polyglot
MYMOD_KEY1,,eng1
MYMOD_KEY2,,eng2
MYMOD_KEY3,,eng3
```
complex example
```
↓this is meaning of each column
LANGUAGE_THIS_EN,description,English,French,Spanish,German,Italian,Brazilian Portuguese,,Russian,,,Danish,,Swedish,Dutch,Polish,,Japanese,Simplified Chinese,Traditional Chinese,Korean,Czech,Hungarian,Română,Thai,,Hebrew,الإنجليزية,,Icelandic,Gaeilge,,,

Save this to UTF-8 CRLF format (with BOM is okay)

"anything before 'Polyglot,' is ignored"

Polyglot,,

MY_KEY1,desc of key1,english text,french text
MY_KEY2,desc of key2, text(space included) ,french text(end with space) 
MY_KEY3,desc of key3,"You can write text, with comma","Don't add space near quote"
MY_KEY_WITH_MULTILINE,multiline text,"This is a multiline text,
with comment,
and ""quote"" is okay.
","This is (not) a French multiline text,
with comment
and ""quote"" is okay.
"
```
