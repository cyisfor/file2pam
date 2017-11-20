For image sites that are anal enough to check for .zip extensions.

gpg -c somefile.txtrarbz2 | ./file2pam/pack | pamtopng > notstatic.png

pngtopam <notstatic.png | ./file2pam/unpack | gpg --decrypt

4GB size limit can be lifted by making an 8 byte size header, but why would you upload a 4GB image to an image board

No error correction, so if they scale the picture you’re hosed, though you can scale it yourself to add redundancy...

./file2pam/pack <something | pamtopng | convert -sample 10000% - nottiny.png
