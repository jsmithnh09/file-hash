function make
  % MAKE generates the MEX file for MEX_MFILEHASH.
  %
  % See Also: MEX
  
  target = 'mex_mfilehash.c';
  rootdir = fileparts(fileparts(mfilename('fullpath')));
  srcdir = fullfile(rootdir, 'src', 'hashers');
  files = {'sha256.c', 'md5.c', 'crc32.c', 'sha1.c'};
  
  % expand the filepath for each source file.
  for fIdx = 1:numel(files)
    files{fIdx} = fullfile(rootdir, 'src', 'hashers', files{fIdx});
  end
  
  % perform the actual MEX compilation.
  fprintf(1, '#### Compiling MFILEHASH\n');
  mex(target, ['-I', srcdir], files{:}, '-outdir', fullfile(rootdir, 'mex'));
  
  % now target the UUID portion.
  target = 'mex_uuidgen.c';
  srcdir = fullfile(rootdir, 'src', 'uuid');
  files = {'uuid4.c'};
  fprintf(1, '### Compiling UUIDGEN\n');
  mex(target, ['-I', srcdir], files{:}, '-outdir', fullfile(rootdir, 'mex'));


  end