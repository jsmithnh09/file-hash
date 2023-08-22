function hash = uuidgen
    % UUIDGEN generates a Universal Unique Identifier.
    %
    %    uuid = UUIDGEN generates a version 4 UUID. This
    %       consists of cryptographically secure bytes with
    %       version and variant byte masking.
    %
    % See Also: MEX_UUIDGEN
    
    hash = mex_uuidgen();
    
end % uuidgen.m