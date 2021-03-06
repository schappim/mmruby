#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "common.h"
#include "debug.h"
#include "stream.h"

fmemstream *fmemstreamopen(char *mem)
{
  fmemstream *stream = mmrbc_alloc(sizeof(fmemstream));
  stream->pos = 0;
  stream->mem = mem;
  stream->size = strlen(mem);
  return stream;
}

/*
 * the same interface as feof()
 */
int fmemeof(FILE *file)
{
  fmemstream *stream = (fmemstream *)file;
  if (stream->pos < stream->size) {
    return 0;
  } else if (stream->pos == stream->size) {
    return 1;
  } else {
    FATALP("fmemeof error");
  }
  return -1;
}

/*
 * the same interface as fgets()
 */
char *fmemgets(char *s, int max, FILE *file)
{
  if (fmemeof(file) != 0) return NULL;
  fmemstream *stream = (fmemstream *)file;
  char *end = strchr(&stream->mem[stream->pos], (int)'\n');
  int len;
  if (end == NULL) {
    if ( (stream->size - stream->pos) < max ) {
      len = stream->size - stream->pos;
    } else {
      len = max - 1;
    }
  } else {
    len = 1 + (intptr_t)end - (intptr_t)&stream->mem[stream->pos];
  }
  if (len < max) {
    memcpy(s, &stream->mem[stream->pos], len);
    s[len] = '\0';
    stream->pos += len;
  } else {
    memcpy(s, &stream->mem[stream->pos], max - 1);
    s[max] = '\0';
    stream->pos += max - 1;
  }
  return s;
}

StreamInterface *StreamInterface_new(char *c, StreamType type)
{
  StreamInterface *si = mmrbc_alloc(sizeof(StreamInterface));
  si->type = type;
  switch (si->type) {
    case STREAM_TYPE_FILE:
      if( (si->stream = (void *)fopen(c, "r" ) ) == NULL ) {
        FATALP("mmrbc: cannot open program file. (%s)", c);
      } else {
        si->fgetsProc = fgets;
        si->feofProc = feof;
      }
      break;
    case STREAM_TYPE_MEMORY:
      si->stream = (void *)fmemstreamopen(c);
      si->fgetsProc = fmemgets;
      si->feofProc = fmemeof;
      break;
    default:
      FATALP("error at Stream_new()");
  }
  return si;
}

void StreamInterface_free(StreamInterface *si)
{
  switch (si->type) {
    case STREAM_TYPE_FILE:
      fclose(si->stream);
      mmrbc_free(si);
      break;
    case STREAM_TYPE_MEMORY:
      mmrbc_free(si->stream);
      mmrbc_free(si);
      break;
    default:
      FATALP("error at Stream_free()");
  }
}
