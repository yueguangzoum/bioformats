/*
 * #%L
 * OME-XERCES C++ library for working with Xerces C++.
 * %%
 * Copyright © 2006 - 2014 Open Microscopy Environment:
 *   - Massachusetts Institute of Technology
 *   - National Institutes of Health
 *   - University of Dundee
 *   - Board of Regents of the University of Wisconsin-Madison
 *   - Glencoe Software, Inc.
 * %%
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of any organization.
 * #L%
 */

#include <ome/xerces/EntityResolver.h>
#include <ome/xerces/String.h>
#include <ome/xerces/Platform.h>
#include <ome/xerces/dom/Document.h>

#include <ome/test/config.h>

#include <ome/test/test.h>

#include <fstream>
#include <stdexcept>
#include <vector>

namespace xml = ome::xerces;

class XercesTestParameters
{
public:
  std::string filename;

  XercesTestParameters(const std::string& filename):
    filename(filename)
  {}
};

class XercesTest : public ::testing::TestWithParam<XercesTestParameters>
{
public:
  xml::Platform plat;

  std::vector<xml::EntityResolver::RegisterEntity> entities;

  virtual void SetUp()
  {
    entities.push_back(xml::EntityResolver::RegisterEntity("http://www.w3.org/2001/XMLSchema",
                                                           boost::filesystem::path(PROJECT_SOURCE_DIR "/components/specification/released-schema/additions/jar/XMLSchema.xsd")));

    entities.push_back(xml::EntityResolver::RegisterEntity("http://www.w3.org/2001/xml.xsd",
                                                           boost::filesystem::path(PROJECT_SOURCE_DIR "/components/specification/released-schema/additions/jar/xml.xsd")));

    entities.push_back(xml::EntityResolver::RegisterEntity("http://www.openmicroscopy.org/Schemas/OME/2012-06/ome.xsd",
                                                           boost::filesystem::path(PROJECT_SOURCE_DIR "/components/specification/released-schema/2012-06/ome.xsd")));

    entities.push_back(xml::EntityResolver::RegisterEntity("http://www.openmicroscopy.org/Schemas/OME/2012-06/BinaryFile.xsd",
                                                           boost::filesystem::path(PROJECT_SOURCE_DIR "/components/specification/released-schema/2012-06/BinaryFile.xsd")));

    entities.push_back(xml::EntityResolver::RegisterEntity("http://www.openmicroscopy.org/Schemas/OME/2012-06/SA.xsd",
                                                           boost::filesystem::path(PROJECT_SOURCE_DIR "/components/specification/released-schema/2012-06/SA.xsd")));

    entities.push_back(xml::EntityResolver::RegisterEntity("http://www.openmicroscopy.org/Schemas/OME/2012-06/SPW.xsd",
                                                           boost::filesystem::path(PROJECT_SOURCE_DIR "/components/specification/released-schema/2012-06/SPW.xsd")));

    entities.push_back(xml::EntityResolver::RegisterEntity("http://www.openmicroscopy.org/Schemas/OME/2012-06/ROI.xsd",
                                                           boost::filesystem::path(PROJECT_SOURCE_DIR "/components/specification/released-schema/2012-06/ROI.xsd")));

  }
};

TEST_P(XercesTest, DocumentFromFile)
{
  const XercesTestParameters& params = GetParam();

  xml::dom::Document doc(ome::xerces::dom::createDocument(boost::filesystem::path(params.filename)));
}

TEST_P(XercesTest, DocumentFromStream)
{
  const XercesTestParameters& params = GetParam();

  std::ifstream in(params.filename.c_str());

  xml::dom::Document doc(ome::xerces::dom::createDocument(in));
}

TEST_P(XercesTest, DocumentFromString)
{
  const XercesTestParameters& params = GetParam();

  std::string data;

  std::ifstream in(params.filename.c_str());
  in.seekg(0, std::ios::end);
  data.reserve(in.tellg());
  in.seekg(0, std::ios::beg);

  data.assign(std::istreambuf_iterator<char>(in),
              std::istreambuf_iterator<char>());

  xml::dom::Document doc(ome::xerces::dom::createDocument(data));
}

XercesTestParameters params[] =
  {
    XercesTestParameters(PROJECT_SOURCE_DIR "/components/specification/samples/2012-06/18x24y5z5t2c8b-text.ome")
  };

// Disable missing-prototypes warning for INSTANTIATE_TEST_CASE_P;
// this is solely to work around a missing prototype in gtest.
#ifdef __GNUC__
#  if defined __clang__ || defined __APPLE__
#    pragma GCC diagnostic ignored "-Wmissing-prototypes"
#  endif
#  pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif

INSTANTIATE_TEST_CASE_P(XercesVariants, XercesTest, ::testing::ValuesIn(params));
