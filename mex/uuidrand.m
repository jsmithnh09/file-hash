function hash = uuidrand
    % UUIDRAND generates a Universal Unique Identifier.
    %
    %    uuid = UUIDRAND generates a version 4 UUID. This
    %       consists of cryptographically secure bytes with
    %       version and variant byte masking.
    %
    % See Also: mex_uuidrand
    
    hash = mex_uuidrand();
    
end % uuidrand.m
