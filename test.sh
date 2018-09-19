for f in $2/*.in;
do
   if diff <(./$1 < $f 2>&-) ${f%in}out;
   then
      echo "$f passed .out test"
   else
      echo "$f failed .out test"
   fi

   if diff <(./$1 < $f 2>&1 >&-) ${f%in}err;
   then
      echo "$f passed .err test"
   else
      echo "$f failed .err test"
   fi
done
