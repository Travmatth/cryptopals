#include "set_1.h"

static char	*test_val = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
static char	*test_ans = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

int	main(void)
{
	char	*result = malloc(strlen(test_ans));

	to_base_64((void*)in, strlen(test_val), result, strlen(test_ans)); 
	return 0;
}
