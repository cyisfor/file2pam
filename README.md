For image boards that are anal enough to check for .zip files concatenated to the end of images.

`gpg -c somefile.txtrarbz2 | ./file2pam/pack | pnmtopng -compression 9 > notstatic.png`

`pngtopam <notstatic.png | ./file2pam/unpack | gpg --decrypt`

4GB size limit can be lifted by making an 8 byte size header, but why would you *do* that? Don’t upload 4GB images to an image board.

No error correction, so if they scale the picture, you’re hosed, though you can scale it yourself to add redundancy...

`./file2pam/pack <something | convert -sample 1000% - - | pamtopng -compression 9 > nottiny.png`

`convert -sample 10% nottiny.png - | pngtopam | ./file2pam/unpack > something`

If they color correct the picture, you’re still hosed. Fixing that is way more complicated than just dumping a file to/from pixels. Find a better image board that isn’t run by nannies.

If mods get suspicious that you’re posting static, look up steghide, and find a better image board. :p
