classdef test_uuid < matlab.unittest.TestCase
    % TEST_UUID validates UUIDs (at least for versions 3-5.)
    %
    % See Also: UUIDRAND, UUIDSPACE
    
    properties(Constant)
        % check online for examples.

        INPUT_STRING = 'matlab';
        VNUM_CHAR_IDX = 15;
        ID_ENUMS = {'dns', 'url', 'oid', 'x500'};
        RESULTS_V3_DATA = struct(...
            'dns',  '1caa2357-3213-312d-a9e0-20fbd7db63ff', ...
            'url',  'a7ac109a-a6df-3591-9c45-5b55736f7a6f', ...
            'oid',  '0c1a2ab0-c651-3b4a-b997-6db0eae0adbe', ...
            'x500', 'cf911522-ac81-3f2e-8f9f-13b2fbdfd2fd');

        RESULTS_V5_DATA = struct(...
            'dns',  '91b3587b-fcdf-5449-b0e3-c120e621a450', ...
            'url',  '6a15d2ba-1c62-5963-b4d2-b2f615d925f4', ...
            'oid',  '7e1ecf3f-0a3f-548d-ad9c-f4c79cef5ed0', ...
            'x500', 'a146d289-a243-564f-a12a-bca3e8690134');
    end

    methods(Test)
        function test_v3data(testCase)
            % TEST_V3DATA confirms we get valid namespace-UUIDs.

            for idx = 0:3
                NS_DISP = testCase.ID_ENUMS{idx+1};
                uuid = uuidspace(testCase.INPUT_STRING, 3, idx);
                testCase.verifyTrue(strcmp(uuid, ...
                    testCase.RESULTS_V3_DATA.(NS_DISP)), ...
                    ['UUID namespace failure with version 3 ', upper(NS_DISP)]);
            end
        end
        
        function test_v5data(testCase)
            % TEST_V5DATA confirms we get valid namespace-UUIDs using v5.
            
            for idx = 0:3
                NS_DISP = testCase.ID_ENUMS{idx+1};
                uuid = uuidspace(testCase.INPUT_STRING, 5, idx);
                testCase.verifyTrue(strcmp(uuid, ...
                    testCase.RESULTS_V5_DATA.(NS_DISP)), ...
                    ['UUID namespace failure with version 5 ', upper(NS_DISP)]);
            end
        end
        
        function test_uuidrand(testCase)
            % we simply want to confirm we can get the correct version
            % number and that every UUID is unique.
            
            numIds = 100;
            data = cell(numIds, 1);
            for idx = 1:numIds
                data{idx} = uuidrand();
                testCase.verifyTrue(data{idx}(testCase.VNUM_CHAR_IDX) == '4', ...
                    'Unable to validate version number in UUID-rand.');
            end
            testCase.verifyTrue(numel(unique(data)) == numel(data), ...
                'Generated non-unique version 4 UUIDs.');
        end
    end
end
