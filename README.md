<h1 align="center">
  <br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="https://github.com/Marten4n6/TinyTor"><img src="https://i.imgur.com/BRgdHy3.png" alt="Logo" width="370"></a>
  <br>
  TinyTor
  <br>
</h1>

<h4 align="center">A tiny Tor client implementation (written in C).</h4>

<p align="center">
  <a href="https://github.com/Marten4n6/TinyTor/blob/master/LICENSE.txt">
      <img src="https://img.shields.io/badge/license-GPLv3-blue.svg?style=flat-square" alt="License">
  </a>
  <a href="https://github.com/Marten4n6/TinyTor/issues">
    <img src="https://img.shields.io/github/issues/Marten4n6/TinyTor.svg?style=flat-square" alt="Issues">
  </a>
  <a href="https://github.com/Marten4n6/TinyTor/blob/master/CONTRIBUTING.md">
      <img src="https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat-square" alt="Contributing">
  </a>
</p>

---

Currently **UNDER DEVELOPMENT** and doesn't yet work. <br/>

## Features

TinyTor can be used as a utility to reach [onion services](https://www.torproject.org/docs/onion-services.html) and regular websites via [Tor](https://www.torproject.org/about/overview#thesolution). <br/>
Furthermore, it may be used by developers as a library.

## How To Use

```bash
# Download or clone this repository
$ git clone https://github.com/Marten4n6/TinyTor

# Go into the repository
$ cd TinyTor
```

## Motivation

TinyTor was created to be able to run on systems (Linux) which have limited memory and disk space. <br/>
A primary example of systems with such limitations is the IoT (Internet of Things).

## Technical details

[wolfSSL](https://github.com/wolfSSL/wolfssl) is used for encryption, which has a memory footprint range from 20-100kB (and ~400kB disk space). <br/>
The implementation uses NTOR, which is newer type of handshake and uses [curve25519](https://en.wikipedia.org/wiki/Curve25519) (see tor-spec 4.4.2, 5.1.4). <br/>

| Name                  | Description                                                          |
| --------------------- | -------------------------------------------------------------------- |
| Entry / guard relay     | This is the entry point to the Tor network.                          |
| Middle relay          | Prevents the guard and exit relay from knowing each other.           |
| Exit relay            | Sends traffic to the final destination intended by the client.       |
| Directory authority   | A trusted server where information about the Tor network is stored.  |
| Consensus             | A document where all Tor relays is maintained.         |
| Descriptor            | Contains the public key and a summary of each introduction point.    |

The following steps are followed to create a request over the Tor network:
1. Select a random (hardcoded) directory authority
2. Build a short list of guard, middle and exit relays

## Versioning

TinyTor will be maintained under the Semantic Versioning guidelines as much as possible. <br/>
Releases will be numbered with the follow format:
```
<major>.<minor>.<patch>
```

And constructed with the following guidelines:
- Breaking backward compatibility bumps the major
- New additions without breaking backward compatibility bumps the minor
- Bug fixes and misc changes bump the patch

For more information on SemVer, please visit https://semver.org/.

## Support Tor

The Tor network relies on volunteers to donate bandwidth. <br/>
The more people who run relays, the faster the Tor network will be. <br/>
Please consider running a relay, you can help make the Tor network:
- faster (and therefore more usable)
- more robust against attacks
- more stable in case of outages
- safer for its users (spying on more relays is harder than on a few)

For more information on volunteering, please visit https://www.torproject.org/getinvolved/volunteer.html

## References

- [Tor Protocol Specification](https://gitweb.torproject.org/torspec.git/tree/tor-spec.txt)
- [Mini-tor](https://github.com/wbenny/mini-tor)
- How Tor Works: Part
  [1](https://jordan-wright.com/blog/2015/02/28/how-tor-works-part-one/),
  [2](https://jordan-wright.com/blog/2015/05/09/how-tor-works-part-two-relays-vs-bridges/),
  [3](https://jordan-wright.com/blog/2015/05/14/how-tor-works-part-three-the-consensus/)
- C Programming: A Modern Approach (Second Edition) by K. N. King
- Logo created by [motusora](https://www.behance.net/motusora)

## License

[GPLv3](https://github.com/Marten4n6/TinyTor/blob/master/LICENSE.txt)
