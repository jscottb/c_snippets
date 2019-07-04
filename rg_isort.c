/*
**  insort() -- insertion sort an array of string pointers via strcmp()
**  public domain by Ray Gardner   Denver, CO   12/91
*/

void strsort(char **v, int n)
{
      int i, j;
      char *vtmp;

      for (i = 1; i < n; ++i)
      {
            vtmp = v[i];
            for ( j = i - 1; j >= 0 && strcmp(v[j], vtmp) > 0; --j )
                  v[j+1] = v[j];
            v[j+1] = vtmp;
      }
}
