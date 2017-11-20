For image sites that are anal enough to check for .zip extensions.

gpg -c somefile.txtrarbz2 | ./file2pam/pack | pamtopng > notstatic.png

pngtopam <notstatic.png | ./file2pam/unpack | gpg --decrypt
