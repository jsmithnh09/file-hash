function hash = mfilehash(infile, algo)
    % MFILEHASH computes a file-hash for use within MATLAB.
    %
    %   HASH = MFILEHASH(FILNAME[, ALGO])
    %       FILENAME (char) is the relative or absolute filepath to hash.
    %       ALGO (char) indicates one of the available hashing algorithms.
    %           Default: crc32.
    %           Available Algorithms include: sha256, md5, sha1, crc32.
    %       HASH (char) is the resulting HEX string of the checksum/hash.
    %
    % See Also: PRIVATE_MFILEHASH
    
    if (nargin < 2)
      algo = 'crc32';
    end
    algo = lower(algo);
    if (~isfile(infile))
        error('Input FILE does not exist.');
    elseif (~ismember(algo, {'crc32', 'sha1', 'sha256', 'md5'}))
        error('Input ALGO does not match any known HASH/CHECKSUM.');
    end
    hash = mex_mfilehash(infile, algo);
    
    end % mfilehash