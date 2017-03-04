#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define m 521 //hash table size. It'd better be prime number in order to prevent collision.
#define m2 520 //It will be used in second hash func. for generating new place in hash table.

int h1( int key )
{
	return ( key % m );
}

int h2( int key )
{
    return ( 1 + ( key % m2 ) );
}

int collision( int key, int k )
{
	return ( ( h1( key ) + ( k * h2( key ) ) ) % m );
}


int search( char hashTable[ ][20] , char *word )
{
    int nextIndex = 0;
    int index;
    int isSimilar = 1;
    int key, i;

    for( i = key = 0; i < strlen( word ); i++ )
    {
        key += ( word[ i ]-'a' ) * 26 * i;
    }
    index = h1( key );

    isSimilar = strcmp( hashTable[ index ] , word );

    while( ( hashTable[ index ][ 0 ] != 0 ) && ( isSimilar != 0 ) )
    {
        nextIndex++;

        index = collision( key , nextIndex );

        isSimilar = strcmp( hashTable[ index ] , word );
    }

    return (hashTable[ index ][ 0 ] == 0) ? 0 : 1;

}


int main()
{

	FILE *fptr;

	int index, nextIndex, key, i, j;

	char wordInFile[20], wordOutside[20], fileName[20];

	char hashTable[m][20];

	int isFound = 0;

	//Table is initialed by 0
	for(i = 0; i < m; i++ )
	{
	    for( j = 0; j < 20; j++ )
	    hashTable[ i ][ j ] = 0;

	}
	printf("Write name of dictionary please,\n" );
	scanf("%s", &fileName);

	fptr = fopen( fileName , "r" );

	if( fptr == NULL )
	{
	    puts("Dictionary couldnt open...");
	    exit(1);
	}


	while( !feof( fptr ) )
	{

	    fscanf( fptr , "%s", &fileName );

	    for( i = key = 0; i < strlen( fileName ); i++ )
	    {
	        key += ( fileName[i] - 'a' ) * 26 * i;
	    }

	    index = h1( key );
	    nextIndex = 0;

	    while( hashTable[ index ][ 0 ] != 0 )
	    {
	        nextIndex++;
	        index = collision( key, nextIndex );

	    }

	    strcpy( hashTable[ index ] , fileName );

	}

	fclose( fptr );


	printf("Please a word that you want to find\n");

	scanf("%s", &wordOutside );

	isFound = search( hashTable , wordOutside );

	if(isFound)
	{
		printf("Word has found:\n");
        for( i = 0; i < strlen( wordOutside ); i++)
        {
            printf( "%c", wordOutside[ i ] );
        } 
	}
	else{
		printf("Word couldn't find.\n");
	}

	return 0;


}