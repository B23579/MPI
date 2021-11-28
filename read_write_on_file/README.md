#  MPI I/O Functions

MPI-IO provides a large number of rutines to read and write data from a file `(I/O)`.

Here we will explore the process to `open` and `write ` on the file.  

The routine ` MPI_File_open()` open the file on all processes int the communicator. 

```
int MPI_File_open( MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh)
```

 where ` comm` is the communicator, `filename` is the name of the input/output file `(e.g "hello.text")`, 'info' is used to provide 

additional information, so, here, we will use ` MPI_INFO_NULL`, `fh is file pointer. fh is creat before with the following command

```
MPI_File fh

```

File can be open using a variaty of mode see [here](http://personalpages.to.infn.it/~mignone/MPI/lecture5.pdf) page 10.

MPI allow reading/ write using two different king file pointer:

`Shared file pointer `: file pointer is sheared among all process in the communicator used to open the file. Only one processor can own 
shared pointer for writing or reading at a time. See [here](http://personalpages.to.infn.it/~mignone/MPI/lecture5.pdf) page 10 for detail.


`individual file pointer ` : each process has it own local file pointer for seek, read, and write operations. 


In our example, we want all the processor to write their result on the same file so, we will used

```
int MPI_File_write_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_status *status);
```
