#!/usr/bin/gawk -f

#usage: ./awk_eg0.awk em.data
#运行前
BEGIN {
      printf "Begin initialise\n"
}
#运行中
{
       # print 
       # printf "running\n"
       if($3 > 0)
         print NR, $1, $2 * $3
       if($3 == 0)
         print NR, $1
}
#运行后
END {
      printf "End process\n"
}

