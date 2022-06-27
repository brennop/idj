#ifndef __COMMON_H
#define __COMMON_H

#define CHECK_ERROR(obj)                                                       \
  if (obj == nullptr) {                                                        \
    printf("%s\n", SDL_GetError());                                            \
    exit(1);                                                                   \
  }

#endif // __COMMON_H
