\name{rLSgetDeteqModel}
\alias{rLSgetDeteqModel}

\title{Get the deterministic equivalent (DEQ) of the SP model.}

\description{
 R interface function for LINDO API function \code{LSgetDeteqModel}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetDeteqModel(model,iDeqType)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iDeqType}{An integer specifying the DEQ type (implicit or explicit). Possible values are:
                     \itemize{
                         \item{LS_DETEQ_FREE}
                         \item{LS_DETEQ_IMPLICIT}
                         \item{LS_DETEQ_EXPLICIT}
                     }
                 }
}

\value{
 If successful, rLSgetDeteqModel returns a LINDO API model object referring to the DEQ model; 
 Otherwise, it returns NULL.
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

