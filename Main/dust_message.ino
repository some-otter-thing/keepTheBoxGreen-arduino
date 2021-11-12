char* getDustMessage() {
  if (dust >= 0 && dust < 70) {
    return "Clean ";
  } else if (dust >= 70 && dust < 150) {
    return "Dirty ";
  } else {
    return "Filthy";
  }
}
