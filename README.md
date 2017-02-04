ft_ls - TMoska
===

Recreation of `ls` command with a few options:

```
Mandatory:
-R		Recursively list subdirectories encountered.
-a		Include directory entries whose names begin with a dot (.).
-l		List in long format. If the output is to a terminal, a total sum for all the file sizes is output on a line before the long listing.
-r		Reverse the order of the sort to get reverse lexicographical order or the oldest entries first (or largest files last, if combined with sort by size.
-t		Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

Bonus:
-d		Directories are listed as plain files (not searched recursively).
-g		This option is only available for compatibility with POSIX; it is used to display the group name in the long (-l) format output (the owner name is suppressed).
-o		List in long format, but omit the group id.
-1		Force output to be one entry per line.  This is the default when output is not to a terminal.
```

This projects has been a part of curriculum for [42 University](https://www.42.us.org) ft_ls project.

Usage
---

```
git clone https://github.com/TMoska/ft_ls.git
cd ft_ls
make
./ft_ls [-Radglort1] [file ...]
```

Contributing
---

If you feel like contributing or improving some functions, feel free to submit a [Pull Request](https://github.com/TMoska/ft_ls/pulls).

License
---

MIT License

Copyright (c) 2016 Tomas Moska

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

