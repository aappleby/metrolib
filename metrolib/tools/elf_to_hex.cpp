#include <stdio.h>
#include <elf.h>
#include <sys/stat.h>
#include <filesystem>
#include <string>
#include <vector>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>

namespace fs = std::filesystem;

//------------------------------------------------------------------------------

int main(int argc, char** argv) {

  if (argc < 3) {
    printf("Usage : elf_to_hex <elf_filename> <out_code> <out_rwdata>\n");
    return -1;
  }

  std::string elf_path        = argv[1];
  std::string code_hex_path   = argv[2];
  std::string rwdata_hex_path = argv[3];
  //std::string rodata_hex_path = argv[4];

  if (!fs::is_regular_file(elf_path)) {
    printf("File %s not found\n", elf_path.c_str());
    return -1;
  }

  auto file_size = fs::file_size(elf_path);
  fs::path file_path(elf_path);

  uint8_t* blob = new uint8_t[file_size];
  FILE* f = fopen(elf_path.c_str(), "rb");
  auto result = fread(blob, 1, file_size, f);
  if (result != file_size) {
    printf("fread failed\n");
    exit(-1);
  }
  fclose(f);

  //bool found_code = false;
  //bool found_data = false;

  Elf32_Ehdr& header = *(Elf32_Ehdr*)blob;
  for (int i = 0; i < header.e_phnum; i++) {
    Elf32_Phdr& phdr = *(Elf32_Phdr*)(blob + header.e_phoff + header.e_phentsize * i);
    if (phdr.p_type & PT_LOAD) {

      //assert(phdr.p_filesz % 4 == 0);

      if (phdr.p_flags & PF_X) {
        //assert(!found_code);
        //found_code = true;
        printf("Code   @ 0x%08x = 0x%04x (%5d) bytes, type 0x%x\n", phdr.p_vaddr, phdr.p_filesz, phdr.p_filesz, phdr.p_type);

        uint32_t* words = (uint32_t*)(blob + phdr.p_offset);
        int word_count = phdr.p_filesz / 4;

        FILE* out = fopen(code_hex_path.c_str(), "w");
        for (int i = 0; i < word_count; i++) {
          fprintf(out, "%08X ", words[i]);
          if (i % 8 == 7) fprintf(out, "\n");
        }
        fprintf(out, "\n");
        fclose(out);
      }
      else if (phdr.p_flags & PF_W) {
        //assert(!found_data);
        //found_data = true;
        printf("RWData @ 0x%08x = 0x%04x (%5d) bytes, type 0x%x\n", phdr.p_vaddr, phdr.p_filesz, phdr.p_filesz, phdr.p_type);

        uint32_t* words = (uint32_t*)(blob + phdr.p_offset);
        int word_count = phdr.p_filesz / 4;

        FILE* out = fopen(rwdata_hex_path.c_str(), "w");
        for (int i = 0; i < word_count; i++) {
          fprintf(out, "%08X ", words[i]);
          if (i % 8 == 7) fprintf(out, "\n");
        }
        fprintf(out, "\n");
        fclose(out);
      }

      /*
      else if (phdr.p_flags & PF_R) {
        //assert(!found_data);
        //found_data = true;
        printf("ROData @ 0x%08x = 0x%04x (%5d) bytes, type 0x%x\n", phdr.p_vaddr, phdr.p_filesz, phdr.p_filesz, phdr.p_type);

        uint32_t* words = (uint32_t*)(blob + phdr.p_offset);
        int word_count = phdr.p_filesz / 4;

        FILE* out = fopen(rodata_hex_path.c_str(), "w");
        for (int i = 0; i < word_count; i++) {
          fprintf(out, "%08X ", words[i]);
          if (i % 8 == 7) fprintf(out, "\n");
        }
        fprintf(out, "\n");
        fclose(out);
      }
      */
    }
  }

  return 0;
}

//------------------------------------------------------------------------------
