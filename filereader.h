#ifndef FILEREADER
#define FILEREADER
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// -- RETURN: zero if success, negative number if fail.

#define null 0
#define ENDOFFILE -1

class FileReader {
public:
	FileReader();
	FileReader(char *_filepath);
	~FileReader();
	int ReadAllContent();			// -- Cita cijeli sadrzaj datoteke u memoriju.
	int GetNumber(float &);			// -- Dohvaca sljedecu float vrijednost u referencu.
	int GetNumber(int &);			// -- Dohvaca sljedecu int vrijednost u referencu.
	void CleanFile();				// -- Ne triba zvat ovu funkciju
	int GetElements();
	int FindCount();
	void Reset();


protected:
	char *filepath;
	char *content;
	char *ptrcont;
	size_t readsize;

};

int FileReader::FindCount()
{
	int br = 0, temp = null, status = null;

	do
	{
		status = this->GetNumber(temp);
		if (status != ENDOFFILE)
		{
			++br;
		}
		else
		{
			break;
		}
	} while (1);

	this->Reset();

	return br;
}

void FileReader::Reset()
{
	ptrcont = content;
}
void FileReader::CleanFile()
{
	do
	{
		if (*ptrcont == '\n' || *ptrcont == '\t' || *ptrcont == '\r')
		{
			*ptrcont = ' ';
		}

		ptrcont++;
	} while (*ptrcont);

	ptrcont = content;
}

int FileReader::GetNumber(int &_number)
{
	if (ptrcont)
	{
		sscanf(ptrcont, " %d", &_number);
		ptrcont = (strchr(ptrcont, ' '));

		if (ptrcont) {
			do
			{
				ptrcont++;
			} while (*ptrcont == ' ');
		}
		else
		{
			return ENDOFFILE;
		}
	}
	else
	{
		return ENDOFFILE;
	}

	return null;
}

int FileReader::GetNumber(float &_number)
{
	if (ptrcont)
	{
		sscanf(ptrcont, " %f", &_number);
		ptrcont = strchr(ptrcont, ' ');

		if (ptrcont)
		{
			do
			{
				ptrcont++;
			} while (*ptrcont == ' ');
		}
	}
	else
	{
		return ENDOFFILE;
	}

	return null;
}

FileReader::FileReader()
{
	content = null;
	ptrcont = null;
	filepath = null;
	readsize = 0;
}

FileReader::FileReader(char *_filepath)
{
	content = null;
	ptrcont = null;
	readsize = null;
	filepath = _filepath;
}

FileReader::~FileReader()
{
	if (content)
	{
		free(content);
	}

	filepath = content = ptrcont = null;
	readsize = null;
}

int FileReader::ReadAllContent()
{
	FILE *fp = null;
	size_t fsize = null;
	fp = fopen(filepath, "r+b");

	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		fsize = ftell(fp);

		if (fsize)
		{
			content = ptrcont = (char *)calloc(fsize + 1, sizeof(char));

			if (content)
			{
				rewind(fp);
				readsize = fread(ptrcont, sizeof(char), fsize, fp);

				if (readsize != fsize)
				{
					return -3;
				}
				else
				{
					CleanFile();
					return readsize;
				}
			}
			else
			{
				return -2;
			}
		}

		fclose(fp);
	}
	else
	{
		return -1;
	}
}

#endif // FILEREADER

