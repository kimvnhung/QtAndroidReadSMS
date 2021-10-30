#include "webapirequest.h"

#include <QDomDocument>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSslKey>
#include <QUrlQuery>


const QString WebAPIRequest::AUTOFARMER_CERTIFICATE_PATH = "assets:/approval-api.pfx";
const QString WebAPIRequest::AUTOLIKE_CERTIFICATE_PATH = "assets:/approval.pfx";
const QString WebAPIRequest::MT_CERTIFICATE_PATH = "assets:/approval-mt.pfx";

const QString WebAPIRequest::AUTOFARMER_CERT = "-----BEGIN CERTIFICATE-----\n\
MIIEHzCCAwegAwIBAgIDEAACMA0GCSqGSIb3DQEBCwUAMH8xCzAJBgNVBAYTAlVT\n\
MRMwEQYDVQQIDApTb21lLVN0YXRlMRcwFQYDVQQKDA5BdXRvRmFyTWVyIEx0ZDET\n\
MBEGA1UEAwwKQXV0b0Zhcm1lcjEtMCsGCSqGSIb3DQEJARYeY2FAYXBwcm92YWwt\n\
YXBpLmF1dG9mYXJtZXIubmV0MB4XDTIxMDUxMzE1MDMyNloXDTMxMDUxMTE1MDMy\n\
NlowgZwxCzAJBgNVBAYTAlVTMRwwGgYDVQQIExNTdGF0ZSBvciBQcm92aWRlbmNl\n\
MRAwDgYDVQQKEwdDb21wYW55MSQwIgYDVQQDExthcHByb3ZhbC1hcGkuYXV0b2Zh\n\
cm1lci5uZXQxNzA1BgkqhkiG9w0BCQEWKGFwcHJvdmFsLWFwaUBhcHByb3ZhbC1h\n\
cGkuYXV0b2Zhcm1lci5uZXQwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIB\n\
AQCgCbE8Jb+BT0xKRHk+i/dg547OBP/nNrOQcaHZPqqe1QDpKPSl1v2AO4xmBkn2\n\
iUNi/xqEQ1VAOc031JQKhX9zmeOdtJVkOcwZFXaEtfdOMS2KUcgv9wLtoClr5GJX\n\
WTeyhDEi/jagJ+ZlPpzIfNu+o9Xbhf/eDEnNnazUxzhqG5PLqZeCU9kJxJXhM5xn\n\
SOQPgVhmg492PUAqBgAcdSQZ2bthDkWnmpgDm812F0UoNZhG3K4ukYZvgMKBv4wG\n\
p3meOAwu8LzAO5x12M50swqKhanHxQ5tlz/DolU3wa42rLtL16MXDOuf/XyIGXOk\n\
lIwVNIZBD5a95U2hP5sGarH5AgMBAAGjgYUwgYIwCQYDVR0TBAIwADAdBgNVHQ4E\n\
FgQUp+mNjvUzIwc9088voAAsfIxCuMEwHwYDVR0jBBgwFoAUPzWHFhjKrRZUnVUu\n\
H9r1qGQiDY8wNQYDVR0fBC4wLDAqoCigJoYkaHR0cDovL3d3dy55b3VyZG9tYWlu\n\
LmNvbS9jYS9jcmwucGVtMA0GCSqGSIb3DQEBCwUAA4IBAQBEypLTNPb8r32MI7oy\n\
G4xpOONYyHThmvbaBaYEv7OrNNONfmzfK+Urjtc539g3BAtxNzi9t//t/pA/I/vE\n\
v6NXsUEglDRgrhsjwTs/OHOuAg9ylsgLoy3VBQGbOB2Lwcp1QZdfN0h4zds6hsRh\n\
V7ifbe117avrsMMDqr7LdUVIsDlh+K+jk5nIe+w+icTKFQ483C3J1KLaY/IFK5yB\n\
nIZzgX5vnYDyQFTy8USem4iwTt5dY7U3ojgKvr66Whm3/inMjpnabT5xVWvq2QXo\n\
EssFY5P6V1Wk3lb3xQT9NPoXMMaNsqumnV98ahfEf6BLBwkWoe+hCbuWGlCxKY+L\n\
3PC3\n\
-----END CERTIFICATE-----";
const QString WebAPIRequest::AUTOLIKE_CERT = "-----BEGIN CERTIFICATE-----\n\
MIIEAjCCAuqgAwIBAgIDEAACMA0GCSqGSIb3DQEBCwUAMHQxCzAJBgNVBAYTAlVT\n\
MRMwEQYDVQQIDApTb21lLVN0YXRlMRUwEwYDVQQKDAxBdXRvTGlrZSBMdGQxETAP\n\
BgNVBAMMCEF1dG9MaWtlMSYwJAYJKoZIhvcNAQkBFhdjYUBhcHByb3ZhbC5hdXRv\n\
bGlrZS5jYzAeFw0yMTA1MTkxMzQ0MDFaFw0zMTA1MTcxMzQ0MDFaMIGKMQswCQYD\n\
VQQGEwJVUzEcMBoGA1UECBMTU3RhdGUgb3IgUHJvdmlkZW5jZTEQMA4GA1UEChMH\n\
Q29tcGFueTEdMBsGA1UEAxMUYXBwcm92YWwuYXV0b2xpa2UuY2MxLDAqBgkqhkiG\n\
9w0BCQEWHWFwcHJvdmFsQGFwcHJvdmFsLmF1dG9saWtlLmNjMIIBIjANBgkqhkiG\n\
9w0BAQEFAAOCAQ8AMIIBCgKCAQEA5yGt8cjof58lhWJBfILhcMWJlZYoPuktYqok\n\
hv27WSuks3GRg4oRmS+MbLA+N9AvW2v5H0HdowbJs2DT4y0HQUXVWWbW0N3fHIMB\n\
HFTL3zFcT/IwQM9S2ZWJU6IuKeeQbJuwTHUvpq3xzP3mdDE0LinPMHq1x7s6UzqH\n\
g+GiBs12fScJleS1zL6mmELH1Dt+LMj0OU9Hb1yQI8VuTuMDFsH3uBzO5jr1+v+d\n\
oulzV3nWjpOqDSWaSDtwaIoO1hQ5y55KJOED6FRyf5jbBNIhHLVBnZtfSaAECdHb\n\
NSIjfj53VduxC3jUdRyHejy+LgGiMjQJs4kT2WaFQCnQBWMaNQIDAQABo4GFMIGC\n\
MAkGA1UdEwQCMAAwHQYDVR0OBBYEFMFNekZ1s2r+JunVZEHVZKpT7My+MB8GA1Ud\n\
IwQYMBaAFJzh4i1be2/cu19V0nQLJsyzAYMXMDUGA1UdHwQuMCwwKqAooCaGJGh0\n\
dHA6Ly93d3cueW91cmRvbWFpbi5jb20vY2EvY3JsLnBlbTANBgkqhkiG9w0BAQsF\n\
AAOCAQEAok5W0C8DRww7Fp+Ba+/xbYCOjqq/TZOpgUGIM2u369jO96yMkxSmaV5y\n\
zqO9KSg48aQMkfdG4PJzLpb+ai3//bewKfmpxgrY+v/DmiuvCYhySs8xLjoblT83\n\
SQpK4vzA8rs3mdB5YdlHWX3Cdvv6oK6+YNAqZ05tUJtNQcXhfVrBe/5HJUCYwWnn\n\
L/VLGVwOS2FPHRd/FT1t9EtiobG+DKLTKXrEIW9OVUn4OMEpRqzUgrrS7RvImcfM\n\
uJdUG3+i/K0DcUQwj0MKGg/Jheoze3eS9KRi0ghLdvnEiqf4pOA6KL7Y3rQG1lQ9\n\
b3n3fi/8oYUE5prtCbSclPYxdKTNSA==\n\
-----END CERTIFICATE-----";
const QString WebAPIRequest::MT_CERT = "-----BEGIN CERTIFICATE-----\n\
MIIEIDCCAwigAwIBAgIDEAACMA0GCSqGSIb3DQEBCwUAMIGPMQswCQYDVQQGEwJV\n\
UzETMBEGA1UECAwKU29tZS1TdGF0ZTEiMCAGA1UECgwZYXBwcm92YWwubW90dHJp\n\
ZXUuY29tIEx0ZDEeMBwGA1UEAwwVYXBwcm92YWwubW90dHJpZXUuY29tMScwJQYJ\n\
KoZIhvcNAQkBFhhjYUBhcHByb3ZhbC5tb3R0cmlldS5jb20wHhcNMjEwODAxMTAw\n\
NTMyWhcNMzEwNzMwMTAwNTMyWjCBjDELMAkGA1UEBhMCVVMxHDAaBgNVBAgTE1N0\n\
YXRlIG9yIFByb3ZpZGVuY2UxEDAOBgNVBAoTB0NvbXBhbnkxHjAcBgNVBAMTFWFw\n\
cHJvdmFsLm1vdHRyaWV1LmNvbTEtMCsGCSqGSIb3DQEJARYeYXBwcm92YWxAYXBw\n\
cm92YWwubW90dHJpZXUuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKC\n\
AQEAsUNKXs+rxnIod5awh7osQZ24r71wMDZT+PmiSnSefA6qkuYz4dila+pfISBS\n\
TZx22nn3C59JcteJbiw+obdvFLLBIryYRXDxxvkFJUV2WdYjR/M/150t/p3qcMU+\n\
Zi+vD8erMg7NzPOoqC7rUY4Pp2labdijU++/kSqsUDieJ71p+cu9riBGyd2qXvWG\n\
8V6Rc8B2B3R43B/nJGGTtVsI+51k74VoHMszXqxdJu79hfjCuNWvI1+GvxmEKAbR\n\
asj9epIM++tDgpnpL4339H7tG0YUr3OF5P6YtDIwLowD5M9Xk4a4QiHwmfHgMiUl\n\
5wlWwElbV2Vi2U14nK/0f0d5EQIDAQABo4GFMIGCMAkGA1UdEwQCMAAwHQYDVR0O\n\
BBYEFNNwBXw+WBMc3SjwiWQS2sYUhsWdMB8GA1UdIwQYMBaAFH769rKRX5Np2RH/\n\
tWuuyNBFBZ1LMDUGA1UdHwQuMCwwKqAooCaGJGh0dHA6Ly93d3cueW91cmRvbWFp\n\
bi5jb20vY2EvY3JsLnBlbTANBgkqhkiG9w0BAQsFAAOCAQEAvmBF5w9Ff/fQXcUk\n\
uRaHXmilIJpoUIsxcJl3vRsgZTcaIS3cuW9nfBTkzt8chPQ5IiSK0XcFKZ7MWnF+\n\
zxmgPeIdbX/jIafE3C4WYWAc7FkaCilD3pikzmv/rHvm7t1tvUpnEmHUfYFYGbwz\n\
B22XWA1ubroY5V6+dQVQ6VW821hefrbsobtZv3gCZ6dr5KD5TfKT0+zjuzP3lIpc\n\
4Av8ngT0QvnqAVjqz8ZM1tFvN1bAFUjCanh83/9BVcQ4dxd8IbPQlUtvRl/1KjDM\n\
yQ1TzD6xgDPJbVnvCsTZEkmYSJbBluerv2sH/p40CuIBHmniRzq+DzDhBB3B1N4p\n\
NrhPZg==\n\
-----END CERTIFICATE-----";

const QString WebAPIRequest::AUTOFARMER_KEY = "-----BEGIN ENCRYPTED PRIVATE KEY-----\n\
MIIFHDBOBgkqhkiG9w0BBQ0wQTApBgkqhkiG9w0BBQwwHAQI21LNwXGnyeoCAggA\n\
MAwGCCqGSIb3DQIJBQAwFAYIKoZIhvcNAwcECBlnramWoXQhBIIEyJwAPqKZEZFR\n\
M41gRNuaJ9vEPEZJWrTR4//1Gl/eDjW1wB94JUialGua7Xix98CWuE3bwt4n/xhB\n\
mTXB0kePMJhGyngAqnkLUEp1thVpJ1444m85WIrABsxrpXv8APqaTrPQ+hcCU+M5\n\
ha2SskARmYQFeIu6CwGWBKa1s+kOg7dRG5hlHZiPotgp26JGWLZaDBcfQ9xf9lBO\n\
YCQzmdfVr8pV1Wrh9eZLyeAa5BmvUu/DjhQ+ACoXldSsFeNDQ4F6tEPuZgtM7gwd\n\
RSg9MfTYW+JwCcvAu6vSOQiAFnA8hKw6f4xgDnbK9QsaS9COf0/N4c9Bey7X3B4l\n\
RRnPAeV13kBucK5FsSgq43wDbOZ6DArgIJoPRolCVCw9okzn4EspKI9b/BTkJuk6\n\
nAfhDHWWZY66ZwW8C9aJAJYjPtURPJz7w4y5BZSuLsbEwOLLfDqxDlXgvAfO/L3J\n\
ZxQ7OuyC4RmsNq9+x2SgBQ7ePpKRcytBOGX63ve/IN9C9op/vBbI+v5UI1aJ/af5\n\
Bbvhyav+2g1jPDYKj3hcLgd2hSxu4aviNFpN3e+6YuhlrZ6NdkEFIhEJM56MES+Y\n\
G7foZnLsUkUeXoEVnIms8AQ5+iUslNX5fc8018RtpB7k9JL8gDWowmrZwmeGvZiq\n\
DlcdQaoWUTbfA2uO92cc5Hz6LQjc6cy26/iYyUCXUSsTiMZqTkSckWxvCYwhOEmC\n\
xQ877gnfxAOJ4TzvL99jkyLWCmJZO0hrplCVH5MYccgAvG0ZV35KqPbqdzRAsLwG\n\
WL1dyJM1dGHztLFizXe0xtLBvl03dVxe+BgjL73GZKfacp4v5M2SpEIUgu9obI3x\n\
CvaXkVUv1vHk4M4XbFAl3awaNZAeVnx2ps0go+S7VLTcB4fkfFT52ZJuZVKyALKW\n\
OmfvM97H4M5xOVhHchq8eO3NeG+aetQyvOLeyW251fCZ3ke0P7M5WD2qmnettydB\n\
gsQvjQzBh0qoIID3a03BfVQQ5H592kxjsZoAyP3Uh9w+GHxsGjX/3xEiMvDwOR7B\n\
3QjnwfQHNMFW/93ar49VO2OoiOSRFnU5jDp8iro1hdrZCyRixLWoI9+b/jXRzng0\n\
H1cKHCa2BVLS01n4nnYEO9BZa0J68LxwPZt2Fbjc2ZFIXhL6+DALxMNg1gdJJVK+\n\
BrwR5mCb0VPl7lDrOsI8PzcoDbWOETALJ7GKZTBGYFyyTqp/nTa8NBwljl+jxUQD\n\
kuEWix5OqZ5F9j3OKlQAhf+bVgWjvGBtOJDlRjlTEX9uPjrZt7zuQRj2IODgpCy4\n\
c0w2hzZxAIpyR08ZgkOGQg3QfVflEaVz7IIXJraJyc8nVvdbD0cyXuSRBcx76ZS5\n\
6GU+wHqcB7suD5fOuLWms2fVf7oRVNGVeUwjuNj1I4rULuyhcZbmsP59GXVvd/8z\n\
P6kBsQdEoL3HWWR5MMfjArXZCq+bOkBC9QPX9HtKQvZheVFiSI7o8QzsAmiIkOZt\n\
ELqoDTMJPpR8WxVvwBFW3Wykj/HA1ju9jfamqa0ZV4CoWS4210EipMpKygZAV9U2\n\
0oHe3m+Na7bXLP5lpbiaGyZPanOQmPQEyKOoIUILRK5omzyyePFyq7AroQaiA1to\n\
spqQCl5+LJmjMiRrdspb8Q==\n\
-----END ENCRYPTED PRIVATE KEY-----";
const QString WebAPIRequest::AUTOLIKE_KEY = "-----BEGIN ENCRYPTED PRIVATE KEY-----\n\
MIIFHDBOBgkqhkiG9w0BBQ0wQTApBgkqhkiG9w0BBQwwHAQIXi7l84WsAJwCAggA\n\
MAwGCCqGSIb3DQIJBQAwFAYIKoZIhvcNAwcECDH/YgTcyrdHBIIEyH6MZ1IwOotI\n\
mspt3N87VgcILfJx54sdCHJuLib8R4SnJwARiesJC1pVLF2FhtDaNKdiCGLBM1RX\n\
AdxvL1VmyjZutObDxEzYqKR/MOJPDrWydvr2WW5cyVvkSKqBQ1A3fWjLbVJaXO3p\n\
Gd40FdPU26ic6Ud0i5/NGmSuubUJx/8a6q6NnUVgc1mu2phc+aTtLce7tw9Csmts\n\
7FfAPJXRLKYhtk3HuGz1DjyjBuhAjSxkWUcSzVo8DQz4og2EugexGk3gethFbf/X\n\
Hf9UXC764R5NvVdlEAUisCfMGEvjJU1AHAbpRl2KQFI/I+ofvU4r9R4XHtq4hkj9\n\
IoOZsjAgJY/I1JfX1OTXj7KiwKYGL9iLTNKNRjrCyViDfDnyrAE9fh8aB8jNo+E+\n\
/sAQNeQcwUqZY+OgSCWqkxiuXAtn7WniF32nLJfOCSIfo9aCYC8MnC6VJdh4cne3\n\
SORZ+YjrFnvuOHNBRhW7vOd+BSaW19y5R0rtUGO6x4SY7y+Ahx8zL+17wvln7UXM\n\
jApbEWkVc1o1GBNL2oeacxqQEs9c1Wttr99CuUza/of3jXC/sqr33u9jwAK+tJbr\n\
KRQrobksRr1eFhFCjmPI0IrOnC3VavrXyckLy+k2dCWUi3CySBDxbHa/yLqJVf7E\n\
HgYksAujuYwk3PkBCtK6PSh/nD+yRFzoPI853l1ICoRHlxli8isb5cLfxv6rFADd\n\
/g6+xPlX3kPrMeGkisFXngi4u1NuLSPDJ3gLtzX9XXf5Ge4M4N9FsNnyHbF3qzi+\n\
A0lKHUSvOWLMNvcIyLlE8zM78LIUWLytSWbCr6eyrIuKOV0dLXdez2XBbiFoMTzp\n\
8wFlHrpbjA+oeb8L0nUgZJcXrIZKbLLiKiovoeONckOiR3gCSbSyrjpEyKSFSlzh\n\
vpX5XS/S7Saif5Q5oFytGaedlnXAarhSb3OXr8LMvaH3Cm4kkZpdCfdf/1842c7q\n\
4afREsgyPbAfaKyVG/Cp12YwQI4a57RVbeMxctRE0Wfk24u95Uy/LwfdRPgTmuka\n\
hquIeNMuaMvEXUhBumXk6EIM+R9Vr2Zg5m5neBXofyrWm2Kg/3FuE13XLBkBLKym\n\
hwBS/btSj0MsvzR+bUMMTpueXI+ngcKAJgwjQe+cNG2OOXBoN5rOxRpZZRxWSn9k\n\
3dFNWZtiNCtDuwONvpa9t0tJgyGxbaGZPE1Y1IyVZe8k9I47KARjPNIecU6OC2iB\n\
2py4RPp279vWj/m2wMLAU7CxDS4D1ZI5mGStQDLepYdks14YOsXXIYPzcLSe9yEI\n\
uQdFLIVfrciYhzDY7wVWUSzZOBmekVqo70nONTdDoTF1BfRHvkn1lPkIXidZGHVo\n\
I5yKK1ussy+D8fa7Hx8OsOclqzviQ9212PtdoiyK5O7fOI4ZCjytuj2Nzjdso5pq\n\
WhcDa6x0Q9r/q0vZK1No/Fu1DRDcc1kdrHAgLxRQDK6amA8k/wkHKdkOBF+XtRI8\n\
3IVrpgKTPkbWBl0MngN3W0vUNy6kRNMm26aqQcwz5dKxeXp6FHyp15ZlS4Is4ewq\n\
/EVm7fKRN3AMQTPCstS8zUhs7dK+dTAn8infLB0smndY+IOuF5uAAY0o78h/xaR2\n\
OGQ+gxCMrQ/A9Jeqv0PPBg==\n\
-----END ENCRYPTED PRIVATE KEY-----";
const QString WebAPIRequest::MT_KEY = "-----BEGIN ENCRYPTED PRIVATE KEY-----\n\
MIIFHDBOBgkqhkiG9w0BBQ0wQTApBgkqhkiG9w0BBQwwHAQI4v1nTYMtFoECAggA\n\
MAwGCCqGSIb3DQIJBQAwFAYIKoZIhvcNAwcECDJ2wFKdnespBIIEyJGffU+05mQF\n\
j7Bz+YVYtZkkKRe1Pw5Y7k+aMN19CT+ayNep3pSShXhLwugvoMVEW7OkcYdo6RGD\n\
TkCK1o2M+zD6VI3MSDUgbbWbGCd3py4gX9I0SvFWjgUFnMPZhRnL3kuGrQ/dtVf+\n\
2oaUnxy57UMqMaM7B6H+kO2lN8Jo7awf7o8L16bvUDtldm0WaIbNCnYczJ6XY6Fr\n\
LYXEnDCkzRkYMN/5iXZaDMPKcmCXuKM5U0yblwUdjhxqVhY+4dEilGDn/X/8NNjR\n\
qXWT6KaKIWxeQcb5OR7nBdN5pdQVpq2jizStPNWevHLpymq1q57YusiN/sH3c1IU\n\
vXBtfKCuh33bEyhfm9giCSZRntMZOymtEQNOPqkf104KzX1FS3T+UOIWeekd/WtS\n\
8xbzxSPiIM6BwzoUgF0Y6EzGQzExiKlm7Et3b+d1IR1F/YRcs9nmKvr4nsgY0BKQ\n\
9jEuETmyVofMOtqqSy8TJweu9mk2nNlF6pIVQPkPIw/P7XfOhkcQrxsknQ6Md/WM\n\
u147iMlM1e9p/uuhUC4osK88T4TPFi/bmtIhOeM6u9OIa5w16Sf2fwemkLkR6Qbn\n\
GqhNDhupqjLbyDtGmjKKFQLwpBNiicPFE2Ik4ywyeAwEu/qUScYkmVyRCqbYYn69\n\
WS8bnK/QlatHjOJi4hzbBRdmqXgpqyjxwArJS63/j9p91Tgz9wfzCaOkfXRFD0Ae\n\
D7XleCYw0ncO0OCdK0i3c1v04cs7I9XQCNPedu9yuXU3pzYHzsp0W+amHZoz50+g\n\
tXQjW7iHCGW/Ha4MQdsI/m3xd2qx2AEIl1UTMmxlSyJfrITiGX8Ls+BVzFepkXWU\n\
ccWpKdUM3+ax1PiFGBBdD/nYBtOi94v5ClT7K6QukRXBdmCzHHQ9NOnodq1+78Tp\n\
E3s9sS/s6MTkk8H0BpvQA9yw6jRDtXXDTKkUUoN2Qxn4Wls+M4bHSpeDTJYb9efb\n\
im+BeOxRuvw8vbSyJmqoudUJF14pxE1VfU6UhjjWarQt1c7TFrArCpaL9ZJYvfqx\n\
lXZS4GaTaswIPeIAwcwYn1tdeFkk8gnYlOb6Y0t5ue7ZzZWjE2Hi+QCEgD5iBv/P\n\
YN3VPEFJLbOQBdyv73/Log5g651Qht1gxWbQA/48ZxgR9NaYj+D2SRnhe0KeH4Em\n\
4RmQiOCmW7Z9KrQAOr9hFO2QhZ9Y7Kb5VMZ+iXJIeupNiL5B6dxAvb0xV6K6CnKX\n\
/ngse+T4r6M1RP5a28Ag0oOiytlBX69+lY22rxZJV/tWCyd0HoCQMD9sqrDDBzSM\n\
ueCscsdIbUQFgT9rWC8K5Z08tQ+RUvTCm3eB8QbRYEjI49zpsZceyXiiE5EUg70L\n\
uUjtKcmGFKSNrC2jsJgV3mwrkSBp3GWr63/ZX15OydVkSc80oBXq+fSPTq+jmdfU\n\
5jHjru03UvJJjPt18/8RUOY5aqqmFNMkbYNTdXIjjX9S8IGnnjWFVxKs5YL2+q3j\n\
BStHH6LX8yTwcGB/Lwt+9HbyEAbpR82xHFbiLOvBTMDrhncm7r7xPr7U6R5DDtmn\n\
9XdFhb7EA616HmIFOqasJpjZG+Bv7B9MJXUVtrNeZode7Mg9W0P8PbFne+MDsp/z\n\
t35s/UgTGwK+i+qgUYjVPw==\n\
-----END ENCRYPTED PRIVATE KEY-----";

const QString WebAPIRequest::AUTOFARMER_PASS = "approval-api";
const QString WebAPIRequest::AUTOLIKE_PASS = "approval";
const QString WebAPIRequest::MT_PASS = "approval";

bool WebAPIRequest::isWaitingResponse = false;
WebAPIRequest::RequestQueueItem* WebAPIRequest::currentRequestItem = nullptr;

WebAPIRequest::WebAPIRequest(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &WebAPIRequest::onNetworkResponsed);

    anotherManager = new QNetworkAccessManager(this);
    connect(anotherManager, &QNetworkAccessManager::finished, [](QNetworkReply *reply){
       LOGD("Another reply");
       LOGD("%s",reply->readAll().data());
    });

    requestQueue = QList<RequestQueueItem*>();

    //load cert
//    if(loadPfxCertificate(AUTOLIKE_CERTIFICATE_PATH,AUTOLIKE_PASS)){
//        qDebug()<<"import autolike";
//    }

//    if(loadPfxCertificate(AUTOFARMER_CERTIFICATE_PATH,AUTOFARMER_PASS)){
//        qDebug()<<"Imported auto farm";
//    }

//    if(loadPfxCertificate(MT_CERTIFICATE_PATH,MT_PASS)){
//        qDebug()<<"Imported MT";
//    }
    if(loadPemCertificate(AUTOLIKE_PEM)){
        qDebug()<<"import autolike";
    }

    if(loadPemCertificate(AUTOFARMER_PEM)){
        qDebug()<<"Imported auto farm";
    }

    if(loadPemCertificate(MT_PEM)){
        qDebug()<<"Imported MT";
    }


}

WebAPIRequest::~WebAPIRequest()
{
    if(manager != nullptr){
        delete manager;
    }

}

//publics
void WebAPIRequest::setBody(QString body)
{
    this->body = body;
}


bool WebAPIRequest::loadPfxCertificate(QString certFilename, QString passphrase) {

    QFile certFile(certFilename);
    certFile.open(QFile::ReadOnly);
    QSslCertificate certificate;
    QSslKey key;
    QList<QSslCertificate> importedCerts;
    qDebug()<<__FUNCTION__<<__LINE__;
    bool imported = QSslCertificate::importPkcs12(&certFile, &key, &certificate, &importedCerts, QByteArray::fromStdString(passphrase.toStdString()));

    certFile.close();

    qDebug() << "Imported cert:" << imported;

    if (imported) {
        QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
        QList<QSslCertificate> certs = sslConfig.caCertificates();
        QList<QSslCertificate> localCerts = sslConfig.localCertificateChain();
        localCerts.append(certificate);
        certs.append(importedCerts);

        sslConfig.setLocalCertificateChain(localCerts);
        sslConfig.setCaCertificates(certs);
        sslConfig.setPrivateKey(key);
        if(certFilename == AUTOFARMER_CERTIFICATE_PATH){
            AUTOFARMER_SSL_CONF = sslConfig;
        }else if(certFilename == AUTOLIKE_CERTIFICATE_PATH){
            AUTOLIKE_SSL_CONF = sslConfig;
        }else {
            MT_SSL_CONF = sslConfig;
        }
    }

    return imported;
}

bool WebAPIRequest::loadPemCertificate(PemType pem)
{
    QString pemContent = "";
    QString keyContent = "";
    QString passphrase = "";
    switch (pem) {
        case AUTOFARMER_PEM:
            pemContent = AUTOFARMER_CERT;
            keyContent = AUTOFARMER_KEY;
            passphrase = AUTOFARMER_PASS;
            break;
        case AUTOLIKE_PEM:
            pemContent = AUTOLIKE_CERT;
            keyContent = AUTOLIKE_KEY;
            passphrase = AUTOLIKE_PASS;
            break;
        case MT_PEM:
            pemContent = MT_CERT;
            keyContent = MT_KEY;
            passphrase = MT_PASS;
            break;
    }

    if(pemContent == ""
            || keyContent == ""
            || passphrase == ""){
        return false;
    }

    QSslCertificate pemCertificate(pemContent.toUtf8());
    QSslKey key(keyContent.toUtf8(), QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey,passphrase.toUtf8());

    bool imported = !pemCertificate.isNull() && !key.isNull();
    qDebug()<<"Imported cert: "<<imported;
    if(imported){
        QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
        QList<QSslCertificate> certs = sslConfig.caCertificates();
        QList<QSslCertificate> localCerts = sslConfig.localCertificateChain();
        localCerts.append(pemCertificate);

        sslConfig.setLocalCertificateChain(localCerts);
        sslConfig.setCaCertificates(certs);
        sslConfig.setPrivateKey(key);
        switch (pem) {
            case AUTOFARMER_PEM:
                AUTOFARMER_SSL_CONF = sslConfig;
                return true;
            case AUTOLIKE_PEM:
                AUTOLIKE_SSL_CONF = sslConfig;
                return true;
            case MT_PEM:
                MT_SSL_CONF = sslConfig;
                return true;
        }
    }
    return false;
}

void WebAPIRequest::sendReport(Transaction *transaction)
{
    QNetworkRequest request;
    QUrl url = QUrl("https://script.google.com/macros/s/AKfycbyYdD0A0koNfGuN4PU4cocGwtTQkA9-3lrGdRVK2OlM6gbicYSaGf6q0Q/exec");
    QUrlQuery query;
    query.addQueryItem("date",QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm"));
    query.addQueryItem("key",transaction->getCode());
    query.addQueryItem("amount",QString::number(transaction->getValue()));
    query.addQueryItem("success",transaction->getStatus() == Transaction::ACCEPTED?"OK":"Failed");
    query.addQueryItem("smsbody",transaction->getSmsContent());
    query.addQueryItem("sheet_name",transaction->getCode().contains("MT")?"M1":"gicungduoc");

    url.setQuery(query);

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    anotherManager->get(request);
}

QNetworkRequest WebAPIRequest::getRequest()
{
    QNetworkRequest request;
    if(body.toUpper().contains("ALIKE")){
        request.setUrl(QUrl("https://adminapi-autolike.congaubeo.us/api/v1/transactions/active"));
        request.setRawHeader("Authorization","Basic Y29uZ2F1YmVvQDEyMzpjb25nYXViZW9AMTIz");
        if(!AUTOLIKE_SSL_CONF.isNull()){
            request.setSslConfiguration(AUTOLIKE_SSL_CONF);
        }
    }else if(body.toUpper().contains("AFARM")){
        request.setUrl(QUrl("https://approval-api.autofarmer.net/v1/transactions/active"));// without ID
        request.setRawHeader("Cache-Control","No-cache");
        if(!AUTOFARMER_SSL_CONF.isNull()){
            request.setSslConfiguration(AUTOFARMER_SSL_CONF);
        }
    }else if(body.toUpper().contains("MT")){
        request.setUrl(QUrl("https://approval.mottrieu.com/api/v1/transactions/active"));
        request.setRawHeader("Authorization","Basic Y29uZ2F1YmVvQDEyMzpjb25nYXViZW9AMTIz");
        if(!AUTOLIKE_SSL_CONF.isNull()){
            request.setSslConfiguration(MT_SSL_CONF);
        }
    }
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Mobile-Secret-Key","3953390b-42bb-11eb-9f8b-1111914b71be");
    return request;
}

void WebAPIRequest::addPostRequest(QString body)
{
    this->setBody(body);
    QNetworkRequest request = getRequest();
    requestQueue.append(new RequestQueueItem(request,body));
    body = "";
}

void WebAPIRequest::postAsync()
{
    if(!isWaitingResponse
            && requestQueue.size() > 0){
        LOGD("");
        manager->post(requestQueue.first()->request,requestQueue.first()->body.toUtf8());
        currentRequestItem = requestQueue.first();
        requestQueue.removeFirst();
        isWaitingResponse = true;
    }
}

QString WebAPIRequest::getAsynBody()
{
    if(currentRequestItem != nullptr){
        return currentRequestItem->body;
    }
    return "";
}

void WebAPIRequest::post(){
    QNetworkRequest request = getRequest();

    manager->post(request,body.toUtf8());
}

void WebAPIRequest::onNetworkResponsed(QNetworkReply *reply)
{
    if(reply != nullptr){
        QByteArray data = reply->readAll();
        LOGD("%s",data.data());
        emit networkResponsed(data);
    }
    isWaitingResponse = false;
    currentRequestItem = nullptr;
    postAsync();
}

//private
QString WebAPIRequest::xmlToHtml(QString xml)
{
    QDomDocument htmlDoc;
    QDomElement htmlRoot = htmlDoc.createElement("html");

    QDomDocument xmlDoc;
    xmlDoc.setContent(xml);
    QDomElement xmlRoot = xmlDoc.documentElement();
    QDomElement xmlItem = xmlRoot.firstChild().toElement();

    while(!xmlItem.isNull())
    {
        //read xml
        int itemId = xmlItem.attribute("id", "0").toInt();
        QString itemName = xmlItem.attribute("Name", "");

        QDomElement xmlImg = xmlItem.firstChild().toElement();
        QString imgSrc;
        int imgId = 0;
        if (!xmlImg.isNull()) {
            imgSrc = xmlImg.attribute("src", "");
            imgId = xmlImg.attribute("id", "0").toInt();
        }

        //create html
        QDomElement htmlItem = htmlDoc.createElement("p");

        QDomElement htmlImg = htmlDoc.createElement("img");
        htmlImg.setAttribute("src", imgSrc);

        QDomElement htmlText = htmlDoc.createElement("p");
        QDomText textName = htmlDoc.createTextNode(itemName);
        htmlText.appendChild(textName);

        htmlItem.appendChild(htmlImg);
        htmlItem.appendChild(htmlText);
        htmlRoot.appendChild(htmlItem);

        //next
        xmlItem = xmlItem.nextSibling().toElement();
    }

    htmlDoc.appendChild(htmlRoot);

    return htmlDoc.toString();
}
