# CSV Guide

The mod is designed to be compat with polyglot's csv format, but not as strict as polyglot's requirement.

- **Only** works with CRLF(`\r\n`), `\n` is seen as a normal character.
- Use UTF-8 encoding. The mod doesn't touch your texts' encoding. The file encoding depends on your usage. For Unity, they use UTF-8.
- All lines before `polyglot,100` will be ignored. You can add comments before that.
- We don't require more comma. e.g. you can write `MY_KEY,desc,english,,\r\n` instead of `MY_KEY,desc,english,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\r\n`. But you need keep the language order.
- Empty value will be ignored and be merged with old value if avaliable.
- Description is ignored.

# Work with Microsoft Excel

You can use `UTF-8 with BOM` encoding to tell excel your csv file is UTF-8 encoding. (UTF-8 with BOM is supported in version `>=0.x.1`)
