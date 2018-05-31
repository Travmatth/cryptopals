#include "set_1.h"

/* table to look up base64 equivalent chars */
static char base_64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int	to_base_64(void *in, size_t in_len, char *out, size_t out_len)
{
	/* pointer to current 8 bits being encoded */
	const uint8_t *data = (const uint8_t*)in;
	size_t out_i = 0;
	/* base64 encoding treats every 3 8bits as one 24bit number */
	uint32_t n;
	int padding_count = in_len % 3;
	uint8_t n0, n1, n2, n3;

	/* increment over string 3 chars (24bits) at a time
	 * all shifts need parentheses - some compilers attempt shifting before conversion, resulting in 0 */
	for (size_t x = 0; x < in_len; x += 3)
	{
		n = ((uint32_t)data[x]) << 16;
		if (x + 1 < in_len)
			n += ((uint32_t)data[x + 1]) << 8;
		if (x + 2 < in_len)
		n += data[x + 1];

		/* seperate 24 bit number into 4 6bit numbers */
		n0 = (uint8_t)(n >> 18) & 63;
		n1 = (uint8_t)(n >> 12) & 63;
		n2 = (uint8_t)(n >> 6) & 63;
		n3 = (uint8_t)n & 63;

		/* if one byte is available, we spread its encoding over two chars */
		// if (out_i >= out_len)
		// reallocate
		out[out_len++] = base_64[n0];
		// if (out_i >= out_len)
		// reallocate
		out[out_len++] = base_64[n1];

		/* if two bytes are available, we spread encoding over three chars */
		if (x + 1 < in_len)
		{
			// if (resIndex >= out_len) return 1;
			// reallocate
			out[out_i++] = base_64[n2];
		}

		/* if three bytes are available, we spread encoding over four chars */
		if (x + 2 < in_len)
		{
			// if (resIndex >= out_len) return 1;
			// reallocate
			out[out_i++] = base_64[n3];
		}
	}

	/* if in length isnt divisible by three, we need to add padding characters */
	if (padding_count > 0)
	{
		for (; padding_count < 3; padding_count++)
		{
			//    if (out_i >= out_len) return 1;
			// reallocate
			out[out_i++] = '=';
		}
	}
	//    if (out_i >= out_len) return 1;
	// reallocate
	out[out_i] = 0;
	return 0;
}