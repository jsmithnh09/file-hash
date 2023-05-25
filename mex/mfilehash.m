function hash = mfilehash(infile, algo, quick)
% MFILEHASH computes a file-hash for use within MATLAB.
%
%   HASH = MFILEHASH(FILNAME[, ALGO[, QUICK]])
%       FILENAME (char) is the relative or absolute filepath to hash.
%       ALGO (char) indicates one of the available hashing algorithms.
%           Default: crc32.
%           Available Algorithms include: sha256, md5, sha1, crc32.
%       QUICK (logical) indicates whether or not to perform a "quick" hash.
%           With larger files, (> 128 KB), we instead hash buffers of the
%           beginning, middle, and end of a large file, (as well as its size.)
%           Default: false
%       HASH (char) is the resulting HEX string of the checksum/hash.
%
% See Also: PRIVATE_MFILEHASH


switch nargin
    case 0
        help(mfilename);
        hash = [];
        return;
    case 1
        algo = 'crc32';
        quick = false;
    case 2
        quick = false;
    otherwise
end
if (~isfile(infile))
    error('Input FILE does not exist.');
elsif (~ismember(algo, {'crc32', 'sha1', 'sha256', 'md5'}))
    error('Input ALGO does not match any known HASH/CHECKSUM.');
end
hash = mex_mfilehash(infile, lower(algo), logical(quick));

end % mfilehash
