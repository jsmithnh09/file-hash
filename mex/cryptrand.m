function y = cryptrand(dims)
% CRYPTRAND generates cryptographically secure random bytes.
%
%   Y = CRYPTRAND([M, N, P, ...]) generates an M-by-N-by-P
%     matrix of random bytes.
%
%    Y = CRYPTRAND(NUMBYTES) will generate NUMBYTES of random
%       values.
%
% See Also: MEX_CRYPTRAND

if (nargin < 1), dims = [1, 1]; end
nelements = prod(dims);
raw = mex_cryptrand(nelements);
y = reshape(raw, dims);

end